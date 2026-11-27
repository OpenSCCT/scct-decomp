#include "versus_build.h"
#include "unreal_math.h"
#include "unreal_object.h"

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

class FArray {
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;

    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FArray()
    {
        if (Data) {
            GMalloc->Free(Data);
            Data = 0;
        }
        ArrayNum = ArrayMax = 0;
    }
    // Retail FArray::AddZeroed pops this and both integer arguments.
    INT __stdcall AddZeroed(INT ElementSize, INT Count);
    void Remove(INT Index, INT Count, INT ElementSize);
};

template<class T> class TArray : public FArray {
public:
    ~TArray();
    INT Num() const { return ArrayNum; }
    T &operator()(INT Index) { return ((T *)Data)[Index]; }
    INT AddZeroed(INT Count = 1) { return FArray::AddZeroed(sizeof(T), Count); }

    void Remove(INT Index, INT Count = 1)
    {
        for (INT i = Index; i < Index + Count; ++i)
            (*this)(i).~T();
        FArray::Remove(Index, Count, sizeof(T));
    }
};

template<class T> TArray<T>::~TArray() { Remove(0, ArrayNum); }

template<class T> inline T Min(T A, T B) { return A <= B ? A : B; }

// The software skinner writes this 32-byte stream format. GetMeshVerts returns its positions.
struct FSkinVertex {
    FVector Position;
    FVector Normal;
    FLOAT U, V;
};
typedef char FSkinVertex_size[sizeof(FSkinVertex) == 0x20 ? 1 : -1];

class FStaticLODModel {
public:
    BYTE Unknown00[0x18];
    INT NumVerts;
    BYTE Unknown1c[0xf4];
};
typedef char FStaticLODModel_size[sizeof(FStaticLODModel) == 0x110 ? 1 : -1];

#include "versus_mesh_instance.h"

class UMesh : public UPrimitive {
public:
    BYTE Unknown50[4];
};
class ULodMesh : public UMesh {};
class USkeletalMesh : public ULodMesh {
public:
    BYTE Unknown54[0x1ac - 0x54];
    TArray<FStaticLODModel> LODModels;
};

class USkeletalMeshInstance : public ULodMeshInstance {
public:
    virtual void GetMeshVerts(AActor *Owner, FVector *Out, INT Stride, INT &Count);
    BYTE Unknown78[0xf0 - 0x78];
    INT CurrentLOD;
};

// Descriptive name. Both retail and the shipped editor call the software skinner here.
void SkinMeshVertices(USkeletalMesh *Mesh, USkeletalMeshInstance *Instance, FSkinVertex *Vertices,
                      INT Stride, INT &VertexCount);

void USkeletalMeshInstance::GetMeshVerts(AActor *Owner, FVector *Out, INT Stride, INT &Count)
{
    USkeletalMesh *Mesh = (USkeletalMesh *)GetMesh();
    if (Mesh->LODModels.Num()) {
        TArray<FSkinVertex> Vertices;
        Vertices.AddZeroed(Mesh->LODModels(0).NumVerts);
        INT VertexCount = 0;
        GetFrame(Owner, 0, 0, 0, VertexCount, GetFrame_Positions);
        Count = Min(Count, Vertices.Num());
        CurrentLOD = 0;
        SkinMeshVertices(Mesh, this, &Vertices(0), sizeof(FSkinVertex), VertexCount);
        FVector *Dest = Out;
        for (INT i = 0; i < Count; ++i) {
            *Dest = Vertices(i).Position;
            Dest = (FVector *)((BYTE *)Dest + Stride);
        }
    } else {
        Count = 0;
    }
}
