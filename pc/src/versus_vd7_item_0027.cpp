// Work item 0027: Versus RVA 0x1270e0-0x127443.
// AActor script native functions: execSetRelativeRotation, execAttachToBone,
// execDetachFromBone, execSetOwner (VC7.0 /GL, linked /LTCG).

typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned __int64 QWORD;

extern "C" double __cdecl sqrt(double);
extern "C" double __cdecl atan2(double, double);
#pragma intrinsic(sqrt, atan2)

#define PI (3.1415926535897932f)

inline FLOAT appSqrt(FLOAT F) { return (FLOAT)sqrt(F); }
inline FLOAT appAtan2(FLOAT Y, FLOAT X) { return (FLOAT)atan2(Y, X); }
inline FLOAT Square(FLOAT F) { return F * F; }

enum EName {
    NAME_None = 0,
    NAME_PROBEMIN = 300,
    NAME_GainedChild = 302,
    NAME_LostChild = 303,
};

struct FName {
    INT Index;
    FName() {}
    FName(EName N) : Index(N) {}
    INT GetIndex() const { return Index; }
    UBOOL operator!=(const FName &Other) const { return Index != Other.Index; }
};

struct FCoords;

struct FVector {
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector operator-() const { return FVector(-X, -Y, -Z); }
    FLOAT operator|(const FVector &V) const { return X * V.X + Y * V.Y + Z * V.Z; }
    FVector TransformVectorBy(const FCoords &Coords) const;
};

struct FRotator {
    INT Pitch, Yaw, Roll;
    FRotator() {}
    FRotator(INT InPitch, INT InYaw, INT InRoll) : Pitch(InPitch), Yaw(InYaw), Roll(InRoll) {}
};

struct FCoords {
    FVector Origin;
    FVector XAxis;
    FVector YAxis;
    FVector ZAxis;
    FCoords() {}
    FCoords(const FVector &InOrigin, const FVector &InX, const FVector &InY, const FVector &InZ)
        : Origin(InOrigin), XAxis(InX), YAxis(InY), ZAxis(InZ) {}
    FCoords &operator*=(const FCoords &TransformCoords);
    FCoords operator*(const FCoords &Coords) const;
    FCoords operator/(const FRotator &Rot) const;
    FCoords Transpose() const;
    FRotator OrthoRotation() const;
};

struct FMatrix {
    FLOAT M[4][4];
    FMatrix() {}
    FMatrix operator*(const FMatrix &Other) const;
    FCoords Coords();
};

struct FRotationMatrix : public FMatrix {
    FRotationMatrix(const FRotator &Rot);
};

struct FTranslationMatrix : public FMatrix {
    FTranslationMatrix(const FVector &Delta);
};

struct FGlobalMath {
    FCoords UnitCoords;
    FLOAT TrigFLOAT[16384];
    void SinCos(INT Angle, FLOAT *OutSin, FLOAT *OutCos);
};
extern FGlobalMath GMath;
extern FVector *GZeroVector_Ptr;

class UObject;
class UClass;
class UFunction;
class UStruct;
class AActor;
class ULevel;
struct FFrame;
struct FStateFrame;

#define RESULT_DECL void *const Result

class __declspec(novtable) FOutputDevice {
public:
    virtual void Serialize(const TCHAR *V, EName Event) = 0;
};

struct FCheckResult {
    FCheckResult *Next;
    AActor *Actor;
    FVector Location;
    FVector Normal;
    void *Primitive;
    FLOAT Time;
    INT Item;
    void *Material;
    INT unk_30;
    UBOOL bNonBlocking;

    FCheckResult(FLOAT InTime, FCheckResult *InNext = 0);
};

class UClass {
public:
    void *VTable;
    DWORD unk_04[8];
    UClass *Class;      // 0x24
    UClass *SuperField; // 0x28
};

class UObject {
public:
    virtual void VSlot00();
    virtual void VSlot01();
    virtual void VSlot02();
    virtual void VSlot03();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = 0);
    virtual void VSlot05(); virtual void VSlot06(); virtual void VSlot07(); virtual void VSlot08();
    virtual void VSlot09(); virtual void VSlot10(); virtual void VSlot11(); virtual void VSlot12();
    virtual void VSlot13(); virtual void VSlot14(); virtual void VSlot15(); virtual void VSlot16();
    virtual void VSlot17(); virtual void VSlot18(); virtual void VSlot19(); virtual void VSlot20();
    virtual void VSlot21(); virtual void VSlot22(); virtual void VSlot23(); virtual void VSlot24();
    virtual void VSlot25(); virtual void VSlot26(); virtual void VSlot27(); virtual void VSlot28();
    virtual void VSlot29(); virtual void VSlot30(); virtual void VSlot31(); virtual void VSlot32();
    virtual void VSlot33(); virtual void VSlot34(); virtual void VSlot35(); virtual void VSlot36();
    virtual void VSlot37(); virtual void VSlot38(); virtual void VSlot39(); virtual void VSlot40();
    virtual void VSlot41(); virtual void VSlot42(); virtual void VSlot43(); virtual void VSlot44();
    virtual void VSlot45(); virtual void VSlot46();
    virtual void SetBase(AActor *NewBase, FVector *NewFloor, UBOOL bNotifyActor);

    UFunction *FindFunctionChecked(FName Name, INT Global = 0);

    INT Index;               // 0x04
    UObject *HashNext;       // 0x08
    FStateFrame *StateFrame; // 0x0c
    DWORD unk_10[5];         // 0x10..0x23
    UClass *Class;           // 0x24

    UBOOL IsA(UClass *SomeBase) const
    {
        for (UClass *TempClass = Class; TempClass; TempClass = TempClass->SuperField)
            if (TempClass == SomeBase)
                return 1;
        return 0;
    }

    INT IsProbing(FName ProbeName);
};

typedef void (UObject::*Native)(FFrame &Stack, RESULT_DECL);
extern Native GNatives[];

struct FFrame : public FOutputDevice {
    UStruct *Node;
    UObject *Object;
    BYTE *Code;
    BYTE *Locals;

    void Step(UObject *Context, RESULT_DECL)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
};

#pragma pack(push, 4)
struct FStateFrame : public FFrame {
    BYTE unk_14[0x08];
    QWORD ProbeMask; // 0x1c
};
#pragma pack(pop)

inline INT UObject::IsProbing(FName ProbeName)
{
    return !StateFrame
        || (StateFrame->ProbeMask & ((QWORD)1 << (ProbeName.GetIndex() - NAME_PROBEMIN)));
}

#define P_GET_OBJECT(Cls, Var) Cls *Var = 0; Stack.Step(Stack.Object, &Var)
#define P_GET_ACTOR(Var) P_GET_OBJECT(AActor, Var)
#define P_GET_NAME(Var) FName Var(NAME_None); Stack.Step(Stack.Object, &Var)
#define P_GET_ROTATOR(Var) FRotator Var; Stack.Step(Stack.Object, &Var)
#define P_FINISH Stack.Code++

class ULevel {
public:
    UBOOL MoveActor(AActor *Actor, const FVector &Delta, const FRotator &NewRotation,
                    FCheckResult &Hit, UBOOL bTest = 0, UBOOL bIgnorePawns = 0,
                    UBOOL bIgnoreBases = 0, UBOOL bNoFail = 0, INT Extra = 0);
};

class AActor : public UObject {
public:
    FMatrix HardRelMatrix;     // 0x28..0x67
    BYTE unk_68[0x80 - 0x68];
    FVector Location;          // 0x80..0x8b
    BYTE unk_8c[0xe0 - 0x8c];
    FRotator Rotation;         // 0xe0..0xeb
    FRotator RelativeRotation; // 0xec..0xf7
    BYTE unk_f8[0x104 - 0xf8];
    AActor *Owner;             // 0x104
    AActor *Base;              // 0x108
    BYTE unk_10c[0x1a4 - 0x10c];
    ULevel *XLevel;            // 0x1a4
    BYTE unk_1a8[0x1bc - 0x1a8];
    UObject *Mesh;             // 0x1bc
    BYTE unk_1c0[0x2b8 - 0x1c0];
    FName AttachmentBone;      // 0x2b8
    BYTE unk_2bc[0x2ec - 0x2bc];
    DWORD unk_2ec_0 : 2;
    DWORD bNetDirty : 1;       // 0x2ec bit 2
    DWORD unk_2ec_3 : 15;
    DWORD bHardAttach : 1;     // 0x2ec bit 18 (0x40000)
    DWORD unk_2ec_19 : 13;
    DWORD unk_2f0_0 : 14;
    DWORD bBlockActors : 1;    // 0x2f0 bit 14 (0x4000)
    DWORD bBlockPlayers : 1;   // 0x2f0 bit 15 (0x8000)
    DWORD unk_2f0_16 : 16;

    void eventLostChild(AActor *Other)
    {
        if (IsProbing(NAME_LostChild)) {
            struct { AActor *Other; } Parms;
            Parms.Other = Other;
            ProcessEvent(FindFunctionChecked(NAME_LostChild), &Parms);
        }
    }
    void eventGainedChild(AActor *Other)
    {
        if (IsProbing(NAME_GainedChild)) {
            struct { AActor *Other; } Parms;
            Parms.Other = Other;
            ProcessEvent(FindFunctionChecked(NAME_GainedChild), &Parms);
        }
    }

    ULevel *GetLevel() const { return XLevel; }

    UBOOL SetRotation(const FRotator &NewRotation)
    {
        FCheckResult Hit(1.f);
        return GetLevel()->MoveActor(this, *GZeroVector_Ptr, NewRotation, Hit);
    }

    UBOOL CheckAttachable();
    void SetOwner(AActor *NewOwner);
    UBOOL AttachToBone(AActor *Attachment, FName BoneName);
    UBOOL DetachFromBone(AActor *Attachment);

    void execSetRelativeRotation(FFrame &Stack, RESULT_DECL);
    void execAttachToBone(FFrame &Stack, RESULT_DECL);
    void execDetachFromBone(FFrame &Stack, RESULT_DECL);
    void execSetOwner(FFrame &Stack, RESULT_DECL);
};

// RVA 0x1270e0
void AActor::execSetRelativeRotation(FFrame &Stack, RESULT_DECL)
{
    P_GET_ROTATOR(NewRotation);
    P_FINISH;

    if (AttachmentBone != NAME_None) {
        RelativeRotation = NewRotation;
        *(UBOOL *)Result = 1;
        return;
    }

    if (Base) {
        if (bHardAttach && !bBlockActors && !bBlockPlayers) {
            FVector OldPos;
            OldPos.X = HardRelMatrix.M[3][0];
            OldPos.Y = HardRelMatrix.M[3][1];
            OldPos.Z = HardRelMatrix.M[3][2];
            HardRelMatrix = FRotationMatrix(NewRotation) * FTranslationMatrix(OldPos);
            FMatrix BaseTM = FRotationMatrix(Base->Rotation) * FTranslationMatrix(Base->Location);
            FMatrix NewWorldTM = HardRelMatrix * BaseTM;
            NewRotation = (GMath.UnitCoords * NewWorldTM.Coords()).OrthoRotation();
        } else {
            FCoords BaseCoords = GMath.UnitCoords / Base->Rotation;
            FCoords Coords = GMath.UnitCoords / NewRotation;
            Coords = Coords * BaseCoords.Transpose();
            NewRotation = Coords.OrthoRotation();
        }
    }

    *(UBOOL *)Result = SetRotation(NewRotation);
}

// RVA 0x127330
void AActor::execAttachToBone(FFrame &Stack, RESULT_DECL)
{
    P_GET_ACTOR(Attachment);
    P_GET_NAME(BoneName);
    P_FINISH;

    if (!Attachment) {
        *(UBOOL *)Result = 0;
        return;
    }

    *(UBOOL *)Result = AttachToBone(Attachment, BoneName);
}

// RVA 0x1273b0
void AActor::execDetachFromBone(FFrame &Stack, RESULT_DECL)
{
    P_GET_ACTOR(Attachment);
    P_FINISH;

    *(UBOOL *)Result = DetachFromBone(Attachment);
}

// RVA 0x127400
void AActor::execSetOwner(FFrame &Stack, RESULT_DECL)
{
    P_GET_ACTOR(NewOwner);
    P_FINISH;

    SetOwner(NewOwner);
}

// ---------------------------------------------------------------------------
// Scaffolding for the link, not part of the unit: LTCG callee bodies copied
// from published Versus units so LINK /LTCG assigns retail register conventions,
// plus drivers rooting the four script natives.

void TransformVector_40ab0(const FCoords &Coords, const FVector &V, FVector &Result);

inline FVector FVector::TransformVectorBy(const FCoords &Coords) const
{
    FVector Result;
    TransformVector_40ab0(Coords, *this, Result);
    return Result;
}

__declspec(noinline) FRotationMatrix::FRotationMatrix(const FRotator &Rot)
{
    FLOAT SR, SP, SY, CR, CP, CY;
    GMath.SinCos(Rot.Yaw, &SY, &CY);
    GMath.SinCos(Rot.Pitch, &SP, &CP);
    GMath.SinCos(Rot.Roll, &SR, &CR);

    M[0][0] = CP * CY;
    M[0][1] = CP * SY;
    M[0][2] = SP;
    M[0][3] = 0.f;

    M[1][0] = SR * SP * CY - CR * SY;
    M[1][1] = SR * SP * SY + CR * CY;
    M[1][2] = -SR * CP;
    M[1][3] = 0.f;

    M[2][0] = -(CR * SP * CY + SR * SY);
    M[2][1] = CY * SR - CR * SP * SY;
    M[2][2] = CR * CP;
    M[2][3] = 0.f;

    M[3][0] = 0.f;
    M[3][1] = 0.f;
    M[3][2] = 0.f;
    M[3][3] = 1.f;
}

__declspec(noinline) void FGlobalMath::SinCos(INT Angle, FLOAT *OutSin, FLOAT *OutCos)
{
    *OutSin = TrigFLOAT[(Angle >> 2) & 16383];
    *OutCos = TrigFLOAT[((Angle + 16384) >> 2) & 16383];
}

__declspec(noinline) void InitMatrix_819b0(FMatrix *M, FLOAT X, FLOAT Y, FLOAT Z)
{
    M->M[0][0] = 1.f; M->M[0][1] = 0.f; M->M[0][2] = 0.f; M->M[0][3] = 0.f;
    M->M[1][0] = 0.f; M->M[1][1] = 1.f; M->M[1][2] = 0.f; M->M[1][3] = 0.f;
    M->M[2][0] = 0.f; M->M[2][1] = 0.f; M->M[2][2] = 1.f; M->M[2][3] = 0.f;
    M->M[3][0] = X;   M->M[3][1] = Y;   M->M[3][2] = Z;   M->M[3][3] = 1.f;
}

__declspec(noinline) FTranslationMatrix::FTranslationMatrix(const FVector &Delta)
{
    InitMatrix_819b0(this, Delta.X, Delta.Y, Delta.Z);
    M[3][3] = 1.f;
}

__declspec(noinline) FMatrix FMatrix::operator*(const FMatrix &Other) const
{
    FMatrix Result;
    Result.M[0][0] = M[0][0] * Other.M[0][0] + M[0][1] * Other.M[1][0] + M[0][2] * Other.M[2][0] + M[0][3] * Other.M[3][0];
    Result.M[0][1] = M[0][0] * Other.M[0][1] + M[0][1] * Other.M[1][1] + M[0][2] * Other.M[2][1] + M[0][3] * Other.M[3][1];
    Result.M[0][2] = M[0][0] * Other.M[0][2] + M[0][1] * Other.M[1][2] + M[0][2] * Other.M[2][2] + M[0][3] * Other.M[3][2];
    Result.M[0][3] = M[0][0] * Other.M[0][3] + M[0][1] * Other.M[1][3] + M[0][2] * Other.M[2][3] + M[0][3] * Other.M[3][3];
    Result.M[1][0] = M[1][0] * Other.M[0][0] + M[1][1] * Other.M[1][0] + M[1][2] * Other.M[2][0] + M[1][3] * Other.M[3][0];
    Result.M[1][1] = M[1][0] * Other.M[0][1] + M[1][1] * Other.M[1][1] + M[1][2] * Other.M[2][1] + M[1][3] * Other.M[3][1];
    Result.M[1][2] = M[1][0] * Other.M[0][2] + M[1][1] * Other.M[1][2] + M[1][2] * Other.M[2][2] + M[1][3] * Other.M[3][2];
    Result.M[1][3] = M[1][0] * Other.M[0][3] + M[1][1] * Other.M[1][3] + M[1][2] * Other.M[2][3] + M[1][3] * Other.M[3][3];
    Result.M[2][0] = M[2][0] * Other.M[0][0] + M[2][1] * Other.M[1][0] + M[2][2] * Other.M[2][0] + M[2][3] * Other.M[3][0];
    Result.M[2][1] = M[2][0] * Other.M[0][1] + M[2][1] * Other.M[1][1] + M[2][2] * Other.M[2][1] + M[2][3] * Other.M[3][1];
    Result.M[2][2] = M[2][0] * Other.M[0][2] + M[2][1] * Other.M[1][2] + M[2][2] * Other.M[2][2] + M[2][3] * Other.M[3][2];
    Result.M[2][3] = M[2][0] * Other.M[0][3] + M[2][1] * Other.M[1][3] + M[2][2] * Other.M[2][3] + M[2][3] * Other.M[3][3];
    Result.M[3][0] = M[3][0] * Other.M[0][0] + M[3][1] * Other.M[1][0] + M[3][2] * Other.M[2][0] + M[3][3] * Other.M[3][0];
    Result.M[3][1] = M[3][0] * Other.M[0][1] + M[3][1] * Other.M[1][1] + M[3][2] * Other.M[2][1] + M[3][3] * Other.M[3][1];
    Result.M[3][2] = M[3][0] * Other.M[0][2] + M[3][1] * Other.M[1][2] + M[3][2] * Other.M[2][2] + M[3][3] * Other.M[3][2];
    Result.M[3][3] = M[3][0] * Other.M[0][3] + M[3][1] * Other.M[1][3] + M[3][2] * Other.M[2][3] + M[3][3] * Other.M[3][3];
    return Result;
}

__declspec(noinline) FCoords FMatrix::Coords()
{
    FCoords Result;
    Result.XAxis = FVector(M[0][0], M[1][0], M[2][0]);
    Result.YAxis = FVector(M[0][1], M[1][1], M[2][1]);
    Result.ZAxis = FVector(M[0][2], M[1][2], M[2][2]);
    Result.Origin = FVector(M[3][0], M[3][1], M[3][2]);
    return Result;
}

__declspec(noinline) FCoords FCoords::Transpose() const
{
    return FCoords(
        -Origin.TransformVectorBy(*this),
        FVector(XAxis.X, YAxis.X, ZAxis.X),
        FVector(XAxis.Y, YAxis.Y, ZAxis.Y),
        FVector(XAxis.Z, YAxis.Z, ZAxis.Z));
}

__declspec(noinline) FCoords FCoords::operator*(const FCoords &Coords) const
{
    return FCoords(*this) *= Coords;
}

__declspec(noinline) FRotator FCoords::OrthoRotation() const
{
    INT Pitch = (INT)(appAtan2(XAxis.Z, appSqrt(Square(XAxis.X) + Square(XAxis.Y))) * (32768.f / PI));
    FRotator R;
    R.Pitch = Pitch;
    INT Yaw = (INT)(appAtan2(XAxis.Y, XAxis.X) * (32768.f / PI));
    R.Yaw = Yaw;
    R.Roll = 0;
    const FCoords S = GMath.UnitCoords / R;
    return FRotator(Pitch, Yaw, (INT)(appAtan2(ZAxis | S.YAxis, YAxis | S.YAxis) * (32768.f / PI)));
}

extern UClass USkeletalMesh_StaticClass;
class USkeletalMeshInstance {
public:
    INT MatchRefBone(FName BoneName);
};
USkeletalMeshInstance *__stdcall GetMeshInstance_df4e0(AActor *Actor);
extern FVector *GDefaultFloor_10ccacbc;

__declspec(noinline) UBOOL AActor::AttachToBone(AActor *Attachment, FName BoneName)
{
    if (Mesh && Mesh->IsA(&USkeletalMesh_StaticClass)) {
        if (GetMeshInstance_df4e0(this)->MatchRefBone(BoneName) > -1 && Attachment && Attachment->CheckAttachable()) {
            Attachment->AttachmentBone = BoneName;
            Attachment->SetBase(this, GDefaultFloor_10ccacbc, 1);
            return 1;
        }
    }
    return 0;
}

__declspec(noinline) UBOOL AActor::DetachFromBone(AActor *Attachment)
{
    if (Mesh && Mesh->IsA(&USkeletalMesh_StaticClass)) {
        Attachment->SetBase(0, GDefaultFloor_10ccacbc, 1);
        Attachment->AttachmentBone.Index = 0;
        return 1;
    }
    return 0;
}

__declspec(noinline) void AActor::SetOwner(AActor *NewOwner)
{
    if (Owner != 0)
        Owner->eventLostChild(this);
    Owner = NewOwner;
    if (Owner != 0)
        Owner->eventGainedChild(this);
    bNetDirty = 1;
}

void Escape(void *);
typedef void (AActor::*ActorNative)(FFrame &, RESULT_DECL);
typedef void (FGlobalMath::*SinCosPtr)(INT, FLOAT *, FLOAT *);

void Driver_1270e0(FMatrix *Out, const FMatrix *A, const FMatrix *B,
                   FCoords *OutC, const FCoords *C1, const FCoords *C2)
{
    Escape(&GMath);
    Escape(GNatives);
    SinCosPtr SC = &FGlobalMath::SinCos;
    Escape(&SC);
    Escape((void *)&InitMatrix_819b0);
    Out[0] = A[0] * B[0];
    Out[1] = A[1] * B[1];
    Out[2] = A[2] * B[2];
    Out[3] = A[3] * B[3];
    Out[4] = A[4] * B[4];
    Out[5] = A[5] * B[5];
    *OutC = *C1 * *C2;
    ActorNative P = &AActor::execSetRelativeRotation;
    Escape(&P);
}

void Driver_127330()
{
    Escape(GNatives);
    Escape(&GDefaultFloor_10ccacbc);
    ActorNative P = &AActor::execAttachToBone;
    Escape(&P);
}

void Driver_1273b0()
{
    Escape(GNatives);
    Escape(&GDefaultFloor_10ccacbc);
    ActorNative P = &AActor::execDetachFromBone;
    Escape(&P);
}

void Driver_127400()
{
    Escape(GNatives);
    ActorNative P = &AActor::execSetOwner;
    Escape(&P);
}
