// Work item w4 0007: Versus RVA 0x123f30-0x1241b7 (AActor skeletal bone/root exec natives).
typedef unsigned short TCHAR;
typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef __int64 SQWORD;

enum EName { NAME_None = 0 };

class FName
{
public:
    INT Index;
    FName() {}
    FName(EName N) : Index(N) {}
};

struct FCoords;

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector operator-() const { return FVector(-X, -Y, -Z); }
    inline FVector TransformVectorBy(const FCoords &Coords) const;
};

struct FRotator
{
    INT Pitch, Yaw, Roll;
    FRotator() {}
    FRotator(INT InPitch, INT InYaw, INT InRoll) : Pitch(InPitch), Yaw(InYaw), Roll(InRoll) {}
};

struct FCoords
{
    FVector Origin, XAxis, YAxis, ZAxis;
    FCoords() {}
    FCoords(const FVector &InOrigin, const FVector &InX, const FVector &InY, const FVector &InZ)
        : Origin(InOrigin), XAxis(InX), YAxis(InY), ZAxis(InZ) {}
    FCoords(const FCoords &Other);
    FCoords operator*(const FCoords &C) const;
    FCoords Transpose() const;
    FRotator OrthoRotation() const;
};

void ASMTransformVector(const FCoords &Coords, const FVector &InVector, FVector &OutVector);

inline FVector FVector::TransformVectorBy(const FCoords &Coords) const
{
    FVector Temp;
    ASMTransformVector(Coords, *this, Temp);
    return Temp;
}

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Num() const { return ArrayNum; }
};

template<class T> class TArray : public FArray
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
};

class UClass;
class UField;
class UStruct;
class UObject;
class AActor;
class UMeshInstance;

struct FOutputDevice
{
    virtual void Serialize(const TCHAR *V, INT Event) = 0;
};

struct FFrame;

class UObject
{
public:
    virtual void V00();
    INT Index;              // +0x04
    UObject *HashNext;      // +0x08
    void *StateFrame;       // +0x0c
    void *_Linker;          // +0x10
    INT _LinkerIndex;       // +0x14
    UObject *Outer;         // +0x18
    DWORD ObjectFlags;      // +0x1c
    FName Name;             // +0x20
    UClass *Class;          // +0x24

    inline UBOOL IsA(UClass *SomeBase) const;
};

typedef void (UObject::*Native)(FFrame &TheStack, void *const Result);
extern Native GNatives[];

struct FFrame : public FOutputDevice
{
    UStruct *Node;
    UObject *Object;
    BYTE *Code;
    BYTE *Locals;

    inline void Step(UObject *Context, void *const Result)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
};

#define RESULT_DECL void *const Result
#define P_GET_NAME(var) FName var(NAME_None); Stack.Step(Stack.Object, &var);
#define P_GET_INT_OPTX(var, def) INT var = def; Stack.Step(Stack.Object, &var);
#define P_GET_UBOOL_OPTX(var, def) UBOOL var = def; Stack.Step(Stack.Object, &var);
#define P_FINISH Stack.Code++;

class UField : public UObject
{
public:
    UField *SuperField;     // +0x28
    UField *Next;           // +0x2c
};

class UStruct : public UField
{
public:
    UField *Children;       // +0x30
};

class UClass : public UStruct
{
public:
    UClass *GetSuperClass() const { return (UClass *)SuperField; }
};

inline UBOOL UObject::IsA(UClass *SomeBase) const
{
    for (UClass *TempClass = Class; TempClass; TempClass = TempClass->GetSuperClass())
        if (TempClass == SomeBase)
            return 1;
    return 0;
}

class UMesh : public UObject
{
public:
    UMeshInstance *MeshGetInstance(const AActor *InActor);
};

class USkeletalMesh : public UMesh
{
public:
    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }
};

class UMeshInstance : public UObject
{
public:
};

extern SQWORD GFrameCounter;

#pragma pack(push, 4)
class USkeletalMeshInstance : public UMeshInstance
{
public:
    virtual void V04(); virtual void V08(); virtual void V0c();
    virtual void V10(); virtual void V14(); virtual void V18(); virtual void V1c();
    virtual void V20(); virtual void V24(); virtual void V28(); virtual void V2c();
    virtual void V30(); virtual void V34(); virtual void V38(); virtual void V3c();
    virtual void V40(); virtual void V44(); virtual void V48(); virtual void V4c();
    virtual void V50(); virtual void V54(); virtual void V58(); virtual void V5c();
    virtual void V60(); virtual void V64(); virtual void V68(); virtual void V6c();
    virtual void V70(); virtual void V74();
    virtual AActor *GetActor();                                                 // slot 30
    virtual void V7c(); virtual void V80(); virtual void V84(); virtual void V88(); virtual void V8c();
    virtual void V90(); virtual void V94(); virtual void V98(); virtual void V9c();
    virtual void Va0(); virtual void Va4(); virtual void Va8(); virtual void Vac();
    virtual void Vb0(); virtual void Vb4(); virtual void Vb8(); virtual void Vbc();
    virtual void Vc0(); virtual void Vc4(); virtual void Vc8(); virtual void Vcc();
    virtual void Vd0(); virtual void Vd4(); virtual void Vd8(); virtual void Vdc();
    virtual void Ve0(); virtual void Ve4(); virtual void Ve8(); virtual void Vec();
    virtual void Vf0(); virtual void Vf4(); virtual void Vf8(); virtual void Vfc();
    virtual void V100(); virtual void V104();
    virtual INT UpdateAnimation(AActor *Owner, INT A, INT B, INT C, INT *D, INT Mode);  // slot 66

    BYTE unk_28[0x5c - 0x28];
    SQWORD LastFrame;                               // +0x5c
    BYTE unk_64[0xb4 - 0x64];
    TArray<FCoords> CachedCoords;                   // +0xb4
    FCoords MeshCoords;                             // +0xc0
    BYTE unk_f0[0x188 - 0xf0];
    FVector RootLocation;                           // +0x188
    FRotator RootRotation;                          // +0x194
    BYTE unk_1a0[0x1e8 - 0x1a0];
    INT unk_1e8;                                    // +0x1e8

    INT MatchRefBone(FName BoneName);
    FCoords GetBoneCoords(DWORD BoneIdx, UBOOL bForce);
    FRotator GetBoneRotation(DWORD BoneIdx, INT Space);
    FVector GetRootLocation();
    FRotator GetRootRotation();
};
#pragma pack(pop)

class AActor : public UObject
{
public:
    BYTE unk_28[0x1bc - 0x28];
    UMesh *Mesh;                                    // +0x1bc
    BYTE unk_1c0[0x1d4 - 0x1c0];
    UMeshInstance *MeshInstance;                    // +0x1d4

    void execGetBoneCoords(FFrame &Stack, RESULT_DECL);
    void execGetBoneRotation(FFrame &Stack, RESULT_DECL);
    void execGetRootLocation(FFrame &Stack, RESULT_DECL);
    void execGetRootRotation(FFrame &Stack, RESULT_DECL);
};

// AActor::execGetBoneCoords (RVA 0x123f30)
void AActor::execGetBoneCoords(FFrame &Stack, RESULT_DECL)
{
    P_GET_NAME(BoneName);
    P_GET_UBOOL_OPTX(bDontCallGetFrame, 0);
    P_FINISH;

    if (Mesh && Mesh->IsA(USkeletalMesh::StaticClass()))
    {
        Mesh->MeshGetInstance(this);
        INT BoneIndex = ((USkeletalMeshInstance *)MeshInstance)->MatchRefBone(BoneName);
        if (BoneIndex >= 0)
            *(FCoords *)Result = ((USkeletalMeshInstance *)MeshInstance)->GetBoneCoords(BoneIndex, bDontCallGetFrame);
        else
            *(FCoords *)Result = ((USkeletalMeshInstance *)MeshInstance)->GetBoneCoords(0, bDontCallGetFrame);
    }
}

// AActor::execGetBoneRotation (RVA 0x124000)
void AActor::execGetBoneRotation(FFrame &Stack, RESULT_DECL)
{
    P_GET_NAME(BoneName);
    P_GET_INT_OPTX(Space, 0);
    P_FINISH;

    if (Mesh && Mesh->IsA(USkeletalMesh::StaticClass()))
    {
        Mesh->MeshGetInstance(this);
        INT BoneIndex = ((USkeletalMeshInstance *)MeshInstance)->MatchRefBone(BoneName);
        if (BoneIndex >= 0)
            *(FRotator *)Result = ((USkeletalMeshInstance *)MeshInstance)->GetBoneRotation(BoneIndex, Space);
        else
            *(FRotator *)Result = FRotator(0, 0, 0);
    }
}

// AActor::execGetRootLocation (RVA 0x1240e0)
void AActor::execGetRootLocation(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;

    if (Mesh && Mesh->IsA(USkeletalMesh::StaticClass()))
    {
        Mesh->MeshGetInstance(this);
        *(FVector *)Result = ((USkeletalMeshInstance *)MeshInstance)->GetRootLocation();
    }
}

// AActor::execGetRootRotation (RVA 0x124150)
void AActor::execGetRootRotation(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;

    if (Mesh && Mesh->IsA(USkeletalMesh::StaticClass()))
    {
        Mesh->MeshGetInstance(this);
        *(FRotator *)Result = ((USkeletalMeshInstance *)MeshInstance)->GetRootRotation();
    }
}

// ---------------------------------------------------------------------------
// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);
INT appRound(FLOAT F);
FLOAT appAtan2(FLOAT Y, FLOAT X);
FLOAT appSqrt(FLOAT F);
void MulCoords(FCoords &A, const FCoords &B);

__declspec(noinline) FCoords FCoords::Transpose() const
{
    return FCoords
    (
        -Origin.TransformVectorBy(*this),
        FVector(XAxis.X, YAxis.X, ZAxis.X),
        FVector(XAxis.Y, YAxis.Y, ZAxis.Y),
        FVector(XAxis.Z, YAxis.Z, ZAxis.Z)
    );
}

__declspec(noinline) FCoords FCoords::operator*(const FCoords &C) const
{
    FCoords R(*this);
    MulCoords(R, C);
    return R;
}

__declspec(noinline) FRotator FCoords::OrthoRotation() const
{
    FRotator R;
    R.Pitch = appRound(appAtan2(XAxis.Z, appSqrt(XAxis.X * XAxis.X + XAxis.Y * XAxis.Y)) * 10430.378f);
    R.Yaw = appRound(appAtan2(XAxis.Y, XAxis.X) * 10430.378f);
    R.Roll = appRound(appAtan2(YAxis.Z, ZAxis.Z) * 10430.378f);
    return R;
}

__declspec(noinline) FRotator USkeletalMeshInstance::GetBoneRotation(DWORD BoneIdx, INT Space)
{
    if (!CachedCoords.Num() || LastFrame < GFrameCounter)
    {
        AActor *Actor = GetActor();
        if (Actor)
        {
            INT UpdateResult;
            UpdateAnimation(Actor, 0, 0, 0, &UpdateResult, 2);
        }
    }
    if (CachedCoords.Num() && BoneIdx < (DWORD)CachedCoords.Num())
    {
        FCoords T = CachedCoords(BoneIdx).Transpose();
        FCoords M = T * MeshCoords;
        FRotator R = M.OrthoRotation();
        return R;
    }
    return FRotator(0, 0, 0);
}

__declspec(noinline) FVector USkeletalMeshInstance::GetRootLocation()
{
    if (unk_1e8)
    {
        AActor *Actor = GetActor();
        if (Actor)
        {
            INT UpdateResult;
            UpdateAnimation(Actor, 0, 0, 0, &UpdateResult, 3);
        }
    }
    return RootLocation;
}

__declspec(noinline) FRotator USkeletalMeshInstance::GetRootRotation()
{
    if (unk_1e8)
    {
        AActor *Actor = GetActor();
        if (Actor)
        {
            INT UpdateResult;
            UpdateAnimation(Actor, 0, 0, 0, &UpdateResult, 3);
        }
    }
    return RootRotation;
}

#pragma inline_depth(0)

typedef void (AActor::*ExecFn)(FFrame &, void *const);

void Driver_124000(USkeletalMeshInstance *M, FRotator *Out, DWORD I)
{
    Escape(GNatives);
    Escape(&USkeletalMesh::PrivateStaticClass);
    Escape(&GFrameCounter);
    ExecFn F = &AActor::execGetBoneRotation;
    Escape(&F);
    *Out = M->GetBoneRotation(I, 0);
}

void Driver_1240e0(USkeletalMeshInstance *M, FVector *Out)
{
    Escape(&USkeletalMesh::PrivateStaticClass);
    ExecFn F = &AActor::execGetRootLocation;
    Escape(&F);
    *Out = M->GetRootLocation();
    Escape(M);
}

USkeletalMeshInstance *UnnamedFindInstance();
void Driver_124150(FRotator *Out)
{
    Escape(&USkeletalMesh::PrivateStaticClass);
    ExecFn F = &AActor::execGetRootRotation;
    Escape(&F);
    *Out = UnnamedFindInstance()->GetRootRotation();
}
