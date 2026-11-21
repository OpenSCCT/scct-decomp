// Work item w4 0009: Versus RVA 0x124580-0x124a56, AActor skeletal animation natives
//   0x124580 AActor::execEnableChannelNotify
//   0x124620 AActor::execSetBoneScale
//   0x1246e0 AActor::execSetBoneLocation
//   0x124810 AActor::execSetBoneRotation
//   0x124940 AActor::execSetBoneDirection
// Built with VC7.0 /GL + /LTCG: the native handlers keep standard thiscall (stored in GNatives),
// while the USkeletalMeshInstance callees receive LTCG register conventions.

typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

#define INDEX_NONE -1
#define RESULT_DECL void *const Result

class __single_inheritance UObject;
class UClass;
class UStruct;
class UMesh;
class UMeshInstance;
class USkeletalMesh;
class USkeletalMeshInstance;
class AActor;
struct FFrame;

class FName
{
public:
    INT Index;
    FName() {}
    FName(INT InIndex) : Index(InIndex) {}
    UBOOL operator==(const FName &Other) const { return Index == Other.Index; }
};

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
};

struct FRotator
{
    INT Pitch, Yaw, Roll;
    FRotator() {}
    FRotator(INT InPitch, INT InYaw, INT InRoll) : Pitch(InPitch), Yaw(InYaw), Roll(InRoll) {}
};

extern const FVector &GDefaultVector; // VA 0x10ccacc0

class FArray
{
public:
    INT Add(INT Count, INT ElementSize);
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

class FOutputDevice
{
public:
    virtual void Serialize(const TCHAR *V, INT Event);
};

typedef void (UObject::*Native)(FFrame &Stack, RESULT_DECL);
extern Native GNatives[];

struct FFrame : public FOutputDevice
{
    UStruct *Node;
    UObject *Object;
    BYTE *Code;
    BYTE *Locals;

    __forceinline void Step(UObject *Context, RESULT_DECL)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
};

#define P_GET_INT(Var) INT Var = 0; Stack.Step(Stack.Object, &Var)
#define P_GET_INT_OPTX(Var, Def) INT Var = Def; Stack.Step(Stack.Object, &Var)
#define P_GET_FLOAT(Var) FLOAT Var = 0.0f; Stack.Step(Stack.Object, &Var)
#define P_GET_FLOAT_OPTX(Var, Def) FLOAT Var = Def; Stack.Step(Stack.Object, &Var)
#define P_GET_NAME(Var) FName Var(0); Stack.Step(Stack.Object, &Var)
#define P_GET_VECTOR_OPTX(Var, Def) FVector Var = Def; Stack.Step(Stack.Object, &Var)
#define P_GET_ROTATOR(Var) FRotator Var; Stack.Step(Stack.Object, &Var)
#define P_GET_ROTATOR_OPTX(Var, Def) FRotator Var = Def; Stack.Step(Stack.Object, &Var)
#define P_FINISH Stack.Code++

class UObject
{
public:
    virtual void VirtualSlot0();
    BYTE unk_4[0x20];
    UClass *Class; // +0x24

    inline UBOOL IsA(UClass *SomeBase) const;
};

class UClass : public UObject
{
public:
    UClass *SuperField; // +0x28

    UClass *GetSuperClass() const { return SuperField; }
};

inline UBOOL UObject::IsA(UClass *SomeBase) const
{
    for (UClass *TempClass = Class; TempClass; TempClass = TempClass->GetSuperClass())
        if (TempClass == SomeBase)
            return 1;
    return SomeBase == 0;
}

class UMesh : public UObject
{
public:
    UMeshInstance *MeshGetInstance(const AActor *Owner); // RVA 0xdf4e0
};

class USkeletalMesh : public UMesh
{
public:
    static UClass PrivateStaticClass; // VA 0x10cc0a78
    static UClass *StaticClass() { return &PrivateStaticClass; }
};

class UMeshInstance : public UObject
{
public:
};

struct FAnimChannel
{
    BYTE unk_0[0x3c];
    INT bNotify;
};

struct FBoneScaler
{
    INT Bone;
    FName Name;
    FLOAT ScaleUniform;
    BYTE unk_c[0x30];
};

struct FBoneDirectionEntry
{
    INT Index;
    FName Name;
    FRotator Turn;
    FVector Trans;
    INT Space;
    FLOAT Alpha;
    FLOAT Alpha2;
    BYTE unk_2c[0x18];
};

class USkeletalMeshInstance : public UMeshInstance
{
public:
    BYTE unk_28[0x74];
    FArray Scalers;          // +0x9c
    BYTE unk_a8[0x7c];
    FArray BoneDirections;   // +0x124
    FArray AnimChannels;     // +0x130

    INT MatchRefBone(FName BoneName);
    void EnableChannelNotify(INT Channel, INT Switch);
    UBOOL SetBoneScale(INT Slot, FLOAT BoneScale, FName BoneName);
    UBOOL SetBoneLocation(FName BoneName, const FVector &BoneTrans, FLOAT Alpha, FLOAT BlendTime, INT Space);
    UBOOL SetBoneRotation(FName BoneName, const FRotator &BoneTurn, INT Space, FLOAT Alpha, FLOAT BlendTime, INT bAdditive);
    UBOOL SetBoneDirection(FName BoneName, const FRotator &BoneTurn, const FVector &BoneTrans, FLOAT Alpha, INT Space);
};

class AActor : public UObject
{
public:
    BYTE unk_28[0x194];
    UMesh *Mesh; // +0x1bc

    void execEnableChannelNotify(FFrame &Stack, RESULT_DECL);
    void execSetBoneScale(FFrame &Stack, RESULT_DECL);
    void execSetBoneLocation(FFrame &Stack, RESULT_DECL);
    void execSetBoneRotation(FFrame &Stack, RESULT_DECL);
    void execSetBoneDirection(FFrame &Stack, RESULT_DECL);
};

// AActor::execEnableChannelNotify
void AActor::execEnableChannelNotify(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(Channel);
    P_GET_INT_OPTX(Switch, 1);
    P_FINISH;
    if (Mesh && Mesh->IsA(USkeletalMesh::StaticClass()))
        ((USkeletalMeshInstance *)Mesh->MeshGetInstance(this))->EnableChannelNotify(Channel, Switch);
}

// AActor::execSetBoneScale
void AActor::execSetBoneScale(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(Slot);
    P_GET_FLOAT_OPTX(BoneScale, 1.0f);
    P_GET_NAME(BoneName);
    P_FINISH;
    if (Mesh && Mesh->IsA(USkeletalMesh::StaticClass()))
        ((USkeletalMeshInstance *)Mesh->MeshGetInstance(this))->SetBoneScale(Slot, BoneScale, BoneName);
}

// AActor::execSetBoneLocation
void AActor::execSetBoneLocation(FFrame &Stack, RESULT_DECL)
{
    P_GET_NAME(BoneName);
    P_GET_VECTOR_OPTX(BoneTrans, GDefaultVector);
    P_GET_FLOAT(Alpha);
    P_GET_FLOAT(BlendTime);
    P_GET_INT(Space);
    P_FINISH;
    if (Mesh && Mesh->IsA(USkeletalMesh::StaticClass()))
        ((USkeletalMeshInstance *)Mesh->MeshGetInstance(this))->SetBoneLocation(BoneName, BoneTrans, Alpha, BlendTime, Space);
}

// AActor::execSetBoneRotation
void AActor::execSetBoneRotation(FFrame &Stack, RESULT_DECL)
{
    P_GET_NAME(BoneName);
    P_GET_ROTATOR_OPTX(BoneTurn, FRotator(0, 0, 0));
    P_GET_INT(Space);
    P_GET_FLOAT_OPTX(Alpha, 1.0f);
    P_GET_FLOAT(BlendTime);
    P_GET_INT(bAdditive);
    P_FINISH;
    if (Mesh && Mesh->IsA(USkeletalMesh::StaticClass()))
        ((USkeletalMeshInstance *)Mesh->MeshGetInstance(this))->SetBoneRotation(BoneName, BoneTurn, Space, Alpha, BlendTime, bAdditive);
}

// AActor::execSetBoneDirection
void AActor::execSetBoneDirection(FFrame &Stack, RESULT_DECL)
{
    P_GET_NAME(BoneName);
    P_GET_ROTATOR(BoneTurn);
    P_GET_VECTOR_OPTX(BoneTrans, GDefaultVector);
    P_GET_FLOAT_OPTX(Alpha, 1.0f);
    P_GET_INT(Space);
    P_FINISH;
    if (Mesh && Mesh->IsA(USkeletalMesh::StaticClass()))
        ((USkeletalMeshInstance *)Mesh->MeshGetInstance(this))->SetBoneDirection(BoneName, BoneTurn, BoneTrans, Alpha, Space);
}

// Scaffolding for the LTCG link, not part of the unit. Stand-in bodies for the
// USkeletalMeshInstance callees give the linker retail's custom register conventions.
void Escape(void *);
INT MatchRefBoneHelper(USkeletalMeshInstance *Inst, FName BoneName);

__declspec(noinline) void USkeletalMeshInstance::EnableChannelNotify(INT Channel, INT Switch)
{
    if (Channel >= 0 && Channel < AnimChannels.ArrayNum)
        ((FAnimChannel *)AnimChannels.Data)[Channel].bNotify = Switch;
}

__declspec(noinline) UBOOL USkeletalMeshInstance::SetBoneScale(INT Slot, FLOAT BoneScale, FName BoneName)
{
    if (Slot < 0 || Slot >= 256)
        return 0;
    INT BoneIdx = MatchRefBone(BoneName);
    if (BoneIdx < 0)
        return 0;
    INT OldNum = Scalers.ArrayNum;
    if (Slot >= OldNum)
        Scalers.Add(Slot - OldNum + 1, sizeof(FBoneScaler));
    ((FBoneScaler *)Scalers.Data)[Slot].Bone = BoneIdx + OldNum;
    ((FBoneScaler *)Scalers.Data)[Slot].Name = BoneName;
    ((FBoneScaler *)Scalers.Data)[Slot].ScaleUniform = BoneScale;
    return 1;
}

__declspec(noinline) UBOOL USkeletalMeshInstance::SetBoneLocation(FName BoneName, const FVector &BoneTrans, FLOAT Alpha, FLOAT BlendTime, INT Space)
{
    FArray *Arr = &BoneDirections;
    if (Arr->ArrayNum >= 256)
        return 0;
    INT Index = MatchRefBoneHelper(this, BoneName);
    if (Index >= 0)
    {
        INT i = INDEX_NONE;
        for (INT j = 0; j < Arr->ArrayNum; j++)
        {
            if (((FBoneDirectionEntry *)Arr->Data)[j].Name == BoneName)
            {
                i = j;
                break;
            }
        }
        if (i < 0)
        {
            i = Arr->ArrayNum;
            Arr->Add(1, sizeof(FBoneDirectionEntry));
            ((FBoneDirectionEntry *)Arr->Data)[i].Name = BoneName;
            ((FBoneDirectionEntry *)Arr->Data)[i].Index = Index;
        }
        ((FBoneDirectionEntry *)Arr->Data)[i].Space = Space;
        ((FBoneDirectionEntry *)Arr->Data)[i].Alpha = Alpha;
        ((FBoneDirectionEntry *)Arr->Data)[i].Alpha2 = BlendTime;
        ((FBoneDirectionEntry *)Arr->Data)[i].Trans = BoneTrans;
        return 1;
    }
    return 0;
}

__declspec(noinline) UBOOL USkeletalMeshInstance::SetBoneRotation(FName BoneName, const FRotator &BoneTurn, INT Space, FLOAT Alpha, FLOAT BlendTime, INT bAdditive)
{
    FArray *Arr = &BoneDirections;
    if (Arr->ArrayNum >= 256)
        return 0;
    INT Index = MatchRefBoneHelper(this, BoneName);
    if (Index >= 0)
    {
        INT i = INDEX_NONE;
        for (INT j = 0; j < Arr->ArrayNum; j++)
        {
            if (((FBoneDirectionEntry *)Arr->Data)[j].Name == BoneName)
            {
                i = j;
                break;
            }
        }
        if (i < 0)
        {
            i = Arr->ArrayNum;
            Arr->Add(1, sizeof(FBoneDirectionEntry));
            ((FBoneDirectionEntry *)Arr->Data)[i].Name = BoneName;
            ((FBoneDirectionEntry *)Arr->Data)[i].Index = Index;
        }
        ((FBoneDirectionEntry *)Arr->Data)[i].Space = Space + bAdditive;
        ((FBoneDirectionEntry *)Arr->Data)[i].Alpha = Alpha;
        ((FBoneDirectionEntry *)Arr->Data)[i].Alpha2 = BlendTime;
        ((FBoneDirectionEntry *)Arr->Data)[i].Turn = BoneTurn;
        return 1;
    }
    return 0;
}

__declspec(noinline) UBOOL USkeletalMeshInstance::SetBoneDirection(FName BoneName, const FRotator &BoneTurn, const FVector &BoneTrans, FLOAT Alpha, INT Space)
{
    if (BoneDirections.ArrayNum >= 256)
        return 0;
    INT Index = MatchRefBone(BoneName);
    if (Index >= 0)
    {
        INT i = INDEX_NONE;
        for (INT j = 0; j < BoneDirections.ArrayNum; j++)
        {
            if (((FBoneDirectionEntry *)BoneDirections.Data)[j].Name == BoneName)
            {
                i = j;
                break;
            }
        }
        if (i < 0)
        {
            i = BoneDirections.ArrayNum;
            BoneDirections.Add(1, sizeof(FBoneDirectionEntry));
            ((FBoneDirectionEntry *)BoneDirections.Data)[i].Name = BoneName;
            ((FBoneDirectionEntry *)BoneDirections.Data)[i].Alpha2 = 0;
            ((FBoneDirectionEntry *)BoneDirections.Data)[i].Index = Index;
        }
        ((FBoneDirectionEntry *)BoneDirections.Data)[i].Space = Space;
        ((FBoneDirectionEntry *)BoneDirections.Data)[i].Alpha = Alpha;
        ((FBoneDirectionEntry *)BoneDirections.Data)[i].Alpha2 = Alpha;
        ((FBoneDirectionEntry *)BoneDirections.Data)[i].Turn = BoneTurn;
        ((FBoneDirectionEntry *)BoneDirections.Data)[i].Trans = BoneTrans;
        return 1;
    }
    return 0;
}

typedef void (AActor::*ActorNative)(FFrame &, RESULT_DECL);
extern ActorNative KeepExecs[5];

void Driver_124580() { Escape(GNatives); KeepExecs[0] = &AActor::execEnableChannelNotify; }
void Driver_124620() { Escape(GNatives); KeepExecs[1] = &AActor::execSetBoneScale; }
void Driver_1246e0() { Escape(GNatives); KeepExecs[2] = &AActor::execSetBoneLocation; }
void Driver_124810() { Escape(GNatives); KeepExecs[3] = &AActor::execSetBoneRotation; }
void Driver_124940() { Escape(GNatives); KeepExecs[4] = &AActor::execSetBoneDirection; }
