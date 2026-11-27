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

class AActor;
class FLevelSceneNode;
class UMesh;
enum EGetFrameTask {
    GetFrame_Render = 0, GetFrame_Positions = 1, GetFrame_Bones = 2, GetFrame_RootMotion = 3
};

class UPrimitive : public UObject {
public:
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();
    virtual void VirtualSlot28();
    virtual void VirtualSlot29();
    BYTE Unknown28[0x28];
};

class UMeshInstance : public UPrimitive {
public:
    virtual AActor *GetActor();
    virtual void VirtualSlot31();
    virtual UMesh *GetMesh();
    virtual void VirtualSlot33();
    virtual void VirtualSlot34();
    virtual void VirtualSlot35();
    virtual void VirtualSlot36();
    virtual void VirtualSlot37();
    virtual void VirtualSlot38();
    virtual void VirtualSlot39();
    virtual void VirtualSlot40();
    virtual void VirtualSlot41();
    virtual void VirtualSlot42();
    virtual void VirtualSlot43();
    virtual void VirtualSlot44();
    virtual void VirtualSlot45();
    virtual void VirtualSlot46();
    virtual void VirtualSlot47();
    virtual void VirtualSlot48();
    virtual void VirtualSlot49();
    virtual void VirtualSlot50();
    virtual void VirtualSlot51();
    virtual void VirtualSlot52();
    virtual void VirtualSlot53();
    virtual void VirtualSlot54();
    virtual void VirtualSlot55();
    virtual void VirtualSlot56();
    virtual void VirtualSlot57();
    virtual void VirtualSlot58();
    virtual void VirtualSlot59();
    virtual void VirtualSlot60();
    virtual void VirtualSlot61();
    virtual void VirtualSlot62();
    virtual void VirtualSlot63();
    virtual void VirtualSlot64();
    virtual void VirtualSlot65();
    virtual void GetFrame(AActor *Owner, FLevelSceneNode *SceneNode, void *Vertices, INT Stride,
                          INT &VertexCount, EGetFrameTask Task);
    virtual void VirtualSlot67();
    virtual void VirtualSlot68();
    virtual void VirtualSlot69();
    virtual void VirtualSlot70();
};

class ULodMeshInstance : public UMeshInstance {
public:
    virtual void GetMeshVerts(AActor *Owner, FVector *Out, INT Stride, INT &Count);
    BYTE Unknown50[0x28];
};

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
