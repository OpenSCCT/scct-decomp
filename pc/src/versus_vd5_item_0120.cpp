// versus_vd5_item_0120.cpp -- skeletal animation channel blend parameters.
/* Versus RVA 0xb6ac0: USkeletalMeshInstance vtable slot 38.
   Matches the shape of UE2 USkeletalMeshInstance::SetBlendParams: stores the
   blend parameters into a 144-byte animation channel and marks it blended.
   The unit was built with VC7.0 /GL and linked /LTCG: ValidateAnimChannel
   (0x109b5910) takes this in EBX and the stage in EDI, which is why this
   function keeps this in EBX. Field names follow UE2 MeshAnimChannel where
   the layout fits; the slot-30 virtual and 0x109c0d50 are unnamed. */
#include "versus_build.h"
#include "unreal_script.h"
class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
};
extern FMalloc *GMalloc;
extern const TCHAR ShrinkingTag[];   /* text not recovered */

class FArray {
public:
    INT Add(INT Count, INT ElementSize);         /* 0x109044e0 */
    INT AddZeroed(INT ElementSize, INT Count);   /* 0x10915400 */
    void Shrink(INT ElementSize)
    {
        if (ArrayMax != ArrayNum) {
            ArrayMax = ArrayNum;
            Data = GMalloc->Realloc(Data, ArrayMax * ElementSize, ShrinkingTag);
        }
    }
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

template <class T> class TArray : public FArray {
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    INT Num() const { return ArrayNum; }
    INT AddZeroed(INT n = 1) { return FArray::AddZeroed(sizeof(T), n); }
    void Shrink();                               /* 0x109c0d50 for MeshAnimChannel */
};

struct MeshAnimChannel {             /* 0x90 bytes */
    BYTE unk_0[0x38];
    FLOAT unk_38;
    BYTE unk_3c[0x4c - 0x3c];
    UBOOL bGlobalPoseCurrent;
    FLOAT CurrentAlpha, CurrentInTime, CurrentOutTime;
    BYTE unk_5c[0x68 - 0x5c];
    INT StartBoneIndex;
    BYTE unk_6c[0x78 - 0x6c];
    FLOAT BlendAlpha;                /* 0x78 */
    FLOAT BlendInTime;               /* 0x7c */
    FLOAT BlendOutTime;              /* 0x80 */
    FName StartBone;                 /* 0x84 */
    UBOOL bGlobalPose;               /* 0x88 */
    UBOOL bBlendSet;                 /* 0x8c */
};

#define MAX_CHANNELS 256

class USkeletalMeshInstance {
public:
    virtual void V00(); virtual void V01(); virtual void V02(); virtual void V03();
    virtual void V04(); virtual void V05(); virtual void V06(); virtual void V07();
    virtual void V08(); virtual void V09(); virtual void V10(); virtual void V11();
    virtual void V12(); virtual void V13(); virtual void V14(); virtual void V15();
    virtual void V16(); virtual void V17(); virtual void V18(); virtual void V19();
    virtual void V20(); virtual void V21(); virtual void V22(); virtual void V23();
    virtual void V24(); virtual void V25(); virtual void V26(); virtual void V27();
    virtual void V28(); virtual void V29();
    virtual UBOOL HasSkeleton();     /* slot 30, +0x78, name assumed */
    UBOOL ValidateAnimChannel(INT Stage);
    INT MatchRefBone(FName Bone);
    UBOOL ApplyBlendParams(INT Stage, FLOAT Alpha, FLOAT InTime, FLOAT OutTime, FName Bone, UBOOL bGlobal);
    void SetBlendParams(INT Stage, FLOAT BlendAlpha, FLOAT InTime, FLOAT OutTime, FName BoneName, UBOOL bGlobalPose);

    unsigned char Pad[0xfc];
    TArray<MeshAnimChannel> Blends;  /* 0x100 */
};

/* 0x109c0d50, defined here so the link sees its register use (array in ESI); not part of the match. */
template <class T> __declspec(noinline) void TArray<T>::Shrink() { FArray::Shrink(sizeof(T)); }

/* 0x109b5910, defined here so the link sees its register use; not part of the match. */
UBOOL USkeletalMeshInstance::ValidateAnimChannel(INT Stage)
{
    if (Stage > MAX_CHANNELS || Stage < 0)
        return 0;
    if (Blends.Num() <= Stage) {
        while (Blends.Num() <= Stage)
            Blends.AddZeroed();
        Blends.Shrink();
    }
    return 1;
}

void USkeletalMeshInstance::SetBlendParams(INT Stage, FLOAT BlendAlpha, FLOAT InTime, FLOAT OutTime, FName BoneName, UBOOL bGlobalPose)
{
    if (Stage >= 0 && ValidateAnimChannel(Stage) && HasSkeleton()) {
        MeshAnimChannel &Channel = Blends(Stage);
        Channel.BlendAlpha = BlendAlpha;
        Channel.BlendInTime = InTime;
        Channel.BlendOutTime = OutTime;
        Channel.StartBone = BoneName;
        Channel.bGlobalPose = bGlobalPose;
        Channel.bBlendSet = 1;
    }
}



// ApplyBlendParams immediately updates a non-base channel and resolves its reference bone.
UBOOL USkeletalMeshInstance::ApplyBlendParams(INT Stage, FLOAT Alpha, FLOAT InTime,
                                            FLOAT OutTime, FName Bone, UBOOL bGlobal)
{
    if (!ValidateAnimChannel(Stage))
        return 0;
    if (!Stage)
        return 0;
    INT BoneIndex = MatchRefBone(Bone);
    if (BoneIndex < 0)
        BoneIndex = 0;
    MeshAnimChannel &Channel = Blends(Stage);
    Channel.CurrentAlpha = Alpha;
    Channel.CurrentInTime = InTime <= 1.f ? InTime : 1.f;
    Channel.CurrentOutTime = OutTime <= 1.f ? OutTime : 1.f;
    Channel.StartBoneIndex = BoneIndex;
    Channel.unk_38 = 0.f;
    Channel.bGlobalPoseCurrent = bGlobal != 0;
    return 1;
}

class UField : public UObject {
public:
    UField *SuperField;
    UField *Next;
};
class UStruct : public UField {
public:
    BYTE unk_30[0x68 - 0x30];
};
class UState : public UStruct {
public:
    BYTE unk_68[0x88 - 0x68];
};
class UClass : public UState {
public:
    UClass *GetSuperClass() const { return (UClass *)SuperField; }
};
class AActor;
class UPrimitive : public UObject {};
class UMesh : public UPrimitive {
public:
    virtual class UMeshInstance *MeshGetInstance(const AActor *Owner);
};
class ULodMesh : public UMesh {};
class USkeletalMesh : public ULodMesh {
public:
    static UClass PrivateStaticClass;
    static USkeletalMesh *Cast(UMesh *Mesh) {
        if (Mesh) {
            for (UClass *Cls = Mesh->GetClass(); Cls; Cls = Cls->GetSuperClass()) {
                if (Cls == &PrivateStaticClass)
                    return (USkeletalMesh *)Mesh;
            }
        }
        return 0;
    }
};
class AActor : public UObject {
public:
    BYTE unk_28[0x1bc - 0x28];
    UMesh *Mesh;
    BYTE unk_1c0[0x1d4 - 0x1c0];
    UMeshInstance *MeshInstance;
    DECLARE_NATIVE(execAnimBlendParams)
};

// execAnimBlendParams reads the six parameters exposed by Engine.Actor.AnimBlendParams.
void AActor::execAnimBlendParams(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(Stage);
    P_GET_FLOAT_OPTX(BlendAlpha, 0.f);
    P_GET_FLOAT_OPTX(InTime, 0.f);
    P_GET_FLOAT_OPTX(OutTime, 0.f);
    P_GET_NAME_OPTX(BoneName, NAME_None);
    P_GET_UBOOL_OPTX(bGlobalPose, 0);
    P_FINISH;
    USkeletalMesh *SkeletalMesh = USkeletalMesh::Cast(Mesh);
    if (SkeletalMesh) {
        SkeletalMesh->UMesh::MeshGetInstance(this);
        USkeletalMeshInstance *Instance = (USkeletalMeshInstance *)MeshInstance;
        Instance->ApplyBlendParams(Stage, BlendAlpha, InTime, OutTime, BoneName, bGlobalPose);
    }
}

// Scaffolding for the link, not part of the unit: retail reaches this
// function only through the vtable, so the driver takes its address.
typedef void (USkeletalMeshInstance::*SetBlendParamsFn)(INT, FLOAT, FLOAT, FLOAT, FName, UBOOL);
void Escape(void *);
void Driver_b6ac0()
{
    SetBlendParamsFn Fn = &USkeletalMeshInstance::SetBlendParams;
    Escape(&Fn);
}
