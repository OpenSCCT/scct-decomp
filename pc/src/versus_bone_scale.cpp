#include "versus_build.h"
#include "unreal_script.h"

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
// The initial allocator dispatches to the C runtime. Engine initialization can replace it.
extern FMalloc GDefaultAllocator;
FMalloc *GMalloc = &GDefaultAllocator;

class FArray {
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    // The retail helper pops the array, element size and count.
    INT __stdcall AddZeroed(INT ElementSize, INT Count);
    void Shrink(INT ElementSize)
    {
        if (ArrayMax != ArrayNum) {
            ArrayMax = ArrayNum;
            Data = GMalloc->Realloc(Data, ArrayMax * ElementSize, L"FArray");
        }
    }
};
template<class T> class TArray : public FArray {
public:
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    INT AddZeroed(INT Count = 1) { return FArray::AddZeroed(sizeof(T), Count); }
    void Shrink() { FArray::Shrink(sizeof(T)); }
};

// The first three members of this 60-byte scaler are written by SetBoneScale.
struct FBoneScaler {
    INT Bone;
    FName Name;
    FLOAT ScaleUniform;
    BYTE unk_c[0x30];
};

class UField : public UObject {
public:
    UField *SuperField;
};
class UStruct : public UField {};
class UState : public UStruct {};
class UClass : public UState {
public:
    UClass *GetSuperClass() const { return (UClass *)SuperField; }
};
inline UBOOL UObject::IsA(UClass *SomeBase) const
{
    for (UClass *Cls = Class; Cls; Cls = Cls->GetSuperClass())
        if (Cls == SomeBase)
            return 1;
    return SomeBase == 0;
}

// The Versus class registrations give UPrimitive and UMeshInstance size 0x50,
// and ULodMeshInstance size 0x78.
class UPrimitive : public UObject {
public:
    BYTE unk_28[0x28];
};
class UMeshInstance : public UPrimitive {};
class ULodMeshInstance : public UMeshInstance {
public:
    BYTE unk_50[0x28];
};
class USkeletalMeshInstance : public ULodMeshInstance {
public:
    BYTE unk_78[0x94];
    TArray<FBoneScaler> Scalers;
    INT MatchRefBone(FName BoneName);
    UBOOL SetBoneScale(INT Slot, FLOAT BoneScale, FName BoneName);
};
class UMesh : public UPrimitive {
public:
    UMeshInstance *MeshGetInstance(const class AActor *Owner);
};
class ULodMesh : public UMesh {};
class USkeletalMesh : public ULodMesh {
public:
    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }
};
class AActor : public UObject {
public:
    BYTE unk_28[0x194];
    UMesh *Mesh;
    DECLARE_NATIVE(execSetBoneScale)
};

void AActor::execSetBoneScale(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(Slot);
    P_GET_FLOAT_OPTX(BoneScale, 1.0f);
    P_GET_NAME(BoneName);
    P_FINISH;
    if (Mesh && Mesh->IsA(USkeletalMesh::StaticClass()))
        ((USkeletalMeshInstance *)Mesh->MeshGetInstance(this))->SetBoneScale(Slot, BoneScale, BoneName);
}

UBOOL USkeletalMeshInstance::SetBoneScale(INT Slot, FLOAT BoneScale, FName BoneName)
{
    if (Slot < 0 || Slot > 256)
        return 0;
    if (Scalers.Num() <= Slot) {
        do {
            Scalers.AddZeroed();
            Scalers(Scalers.Num() - 1).Bone = -1;
        } while (Scalers.Num() <= Slot);
        Scalers.Shrink();
    }
    if (BoneScale != 1.0f && BoneName != NAME_None) {
        INT BoneIndex = MatchRefBone(BoneName);
        if (BoneIndex >= 0) {
            Scalers(Slot).Bone = BoneIndex;
            Scalers(Slot).Name = BoneName;
            Scalers(Slot).ScaleUniform = BoneScale;
        }
    } else {
        Scalers(Slot).Bone = -1;
        Scalers(Slot).Name = NAME_None;
    }
    return 1;
}
