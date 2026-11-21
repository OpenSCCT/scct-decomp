// Work item 0048: Versus RVA 0x12f3f0-0x12f61d.
// AActor::physRootMotion and two AActor probe events (LTCG).

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned char BYTE;
typedef unsigned __int64 QWORD;

enum EName
{
    NAME_None     = 0,
    NAME_PROBEMIN = 0x12c,
    NAME_PROBEMAX = 0x16c
};

class FName
{
public:
    INT Index;
    FName(EName N) : Index(N) {}
    FName(const FName &Other) : Index(Other.Index) {}
    INT GetIndex() const { return Index; }
};

class FVector
{
public:
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}

    FVector operator-(const FVector &V) const
    {
        return FVector(X - V.X, Y - V.Y, Z - V.Z);
    }

    FVector operator/(FLOAT Scale) const
    {
        const FLOAT RScale = 1.f / Scale;
        return FVector(X * RScale, Y * RScale, Z * RScale);
    }
};

extern const FVector *GZeroVector;

#pragma pack(push, 4)
struct FStateFrame
{
    BYTE unk_00[0x1c];
    QWORD ProbeMask;
};
#pragma pack(pop)

class UFunction;
class UClass;
class AActor;

class UObject
{
public:
    virtual void V00();
    virtual void V04();
    virtual void V08();
    virtual void V0c();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = 0);

    INT Index;
    UObject *HashNext;
    FStateFrame *StateFrame;
    BYTE unk_10[0x14];
    UClass *Class;

    UFunction *FindFunctionChecked(FName InName, INT Global = 0);

    UBOOL IsA(UClass *SomeBase) const;

    UBOOL IsProbing(FName ProbeName)
    {
        return (ProbeName.GetIndex() < NAME_PROBEMIN)
            || (ProbeName.GetIndex() >= NAME_PROBEMAX)
            || (!StateFrame)
            || (StateFrame->ProbeMask & ((QWORD)1 << (ProbeName.GetIndex() - NAME_PROBEMIN)));
    }
};

class UClass : public UObject
{
public:
    UClass *SuperField;
};

inline UBOOL UObject::IsA(UClass *SomeBase) const
{
    for (UClass *TempClass = Class; TempClass; TempClass = TempClass->SuperField)
        if (TempClass == SomeBase)
            return 1;
    return 0;
}

class UMeshInstance : public UObject
{
};

class UMesh : public UObject
{
public:
    UMeshInstance *MeshGetInstance(const AActor *Actor);
};

class USkeletalMesh : public UMesh
{
public:
    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }
};

class USkeletalMeshInstance : public UMeshInstance
{
public:
    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }
};

template<class T> inline T *Cast(UObject *Src)
{
    return (Src && Src->IsA(T::StaticClass())) ? (T *)Src : 0;
}

struct FCheckResult
{
    FCheckResult *Next;
    AActor *Actor;
    FVector Location;
    FVector Normal;
    UObject *Primitive;
    FLOAT Time;
    INT Item;
    UObject *Material;
    INT unk_30;
    DWORD unk_34;

    FCheckResult(FLOAT InTime, FCheckResult *InNext = 0);
};

struct AActor_eventProbe137_Parms
{
    FVector V;
};

struct AActor_eventProbe152_Parms
{
    FVector V;
    AActor *Other;
};

class AActor : public UObject
{
public:
    BYTE unk_28[0x80 - 0x28];
    FVector Location;
    FVector Velocity;
    FVector Acceleration;
    BYTE unk_a4[0x1bc - 0xa4];
    UMesh *Mesh;
    BYTE unk_1c0[0x1d4 - 0x1c0];
    UMeshInstance *MeshInstance;
    BYTE unk_1d8[0x2f0 - 0x1d8];
    DWORD unk_2f0_bits0 : 13;
    DWORD bCollideWorld : 1;
    DWORD unk_2f0_bits14 : 16;
    DWORD bDeleteMe : 1;
    DWORD unk_2f0_bit31 : 1;

    void physRootMotion(FLOAT DeltaTime);
    __declspec(noinline) void eventProbe137(FVector V);
    __declspec(noinline) void eventProbe152(FVector V, AActor *Other);
};

// RVA 0x12f3f0 (LTCG: this in EAX, DeltaTime on stack).
// Standard UE2 AActor::physRootMotion physics path: checks Mesh (+0x1bc)
// against PrivateStaticClass 0x10cc0a78, calls 0x109df4e0, checks MeshInstance
// (+0x1d4) against PrivateStaticClass 0x10cc0b90, clears bit 13 of +0x2f0,
// constructs FCheckResult(1.f) at 0x109927b0, and updates Velocity from
// (Location - OldLocation) / DeltaTime when bit 30 is clear.
void AActor::physRootMotion(FLOAT DeltaTime)
{
    USkeletalMesh *SkelMesh = Cast<USkeletalMesh>(Mesh);
    if (!SkelMesh)
    {
        Velocity = *GZeroVector;
        Acceleration = *GZeroVector;
        return;
    }
    SkelMesh->MeshGetInstance(this);
    USkeletalMeshInstance *SkelInst = Cast<USkeletalMeshInstance>(MeshInstance);
    if (!SkelInst)
    {
        Velocity = *GZeroVector;
        Acceleration = *GZeroVector;
        return;
    }
    FVector OldLocation = Location;
    UBOOL bOldCollideWorld = bCollideWorld;
    bCollideWorld = 0;
    FCheckResult Hit(1.f);
    if (!bDeleteMe)
    {
        Velocity = (Location - OldLocation) / DeltaTime;
    }
    bCollideWorld = bOldCollideWorld;
}

// RVA 0x12f560 (LTCG: this in ESI). Probe event for name index 0x137 (probe bit 11).
void AActor::eventProbe137(FVector V)
{
    if (IsProbing(FName((EName)0x137)))
    {
        AActor_eventProbe137_Parms Parms;
        Parms.V = V;
        ProcessEvent(FindFunctionChecked(FName((EName)0x137)), &Parms);
    }
}

// RVA 0x12f5c0 (LTCG: this in ESI). Probe event for name index 0x152 (probe bit 38).
void AActor::eventProbe152(FVector V, AActor *Other)
{
    if (IsProbing(FName((EName)0x152)))
    {
        AActor_eventProbe152_Parms Parms;
        Parms.V = V;
        Parms.Other = Other;
        ProcessEvent(FindFunctionChecked(FName((EName)0x152)), &Parms);
    }
}

// Scaffolding for the LTCG link, not part of the unit. __declspec(noinline) on
// the two probe events stands in for retail call sites the LTCG inliner declined.
void Escape(void *);

void Driver_12f3f0(AActor *A, FLOAT DeltaTime)
{
    Escape(&GZeroVector);
    A->physRootMotion(DeltaTime);
}

void Driver_12f560(AActor *A, AActor *B, AActor *C, FVector V)
{
    A->eventProbe137(V);
    B->eventProbe137(V);
    C->eventProbe137(V);
}

void Driver_12f5c0(AActor *A, AActor *B, AActor *C, FVector V, AActor *Other)
{
    A->eventProbe152(V, Other);
    B->eventProbe152(V, Other);
    C->eventProbe152(V, Other);
}
