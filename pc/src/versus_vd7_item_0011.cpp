// w4_item_0011.cpp -- Versus AActor script setters and AController::CheckHearSound
// RVA 0x124ea0-0x12500d:
// - 0x124ea0: AActor::execSetStaticMesh
// - 0x124ee0: AActor::execSetDrawType
// - 0x124f20: AActor::execSetDrawScale3D
// - 0x124f70: AController::CheckHearSound
#pragma pack(push, 4)

typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef double DOUBLE;
typedef unsigned __int64 QWORD;

#define RESULT_DECL void *const Result

enum { NAME_PROBEMIN = 300, NAME_PROBEMAX = 364 };
enum EName {
    NAME_AIHearSound = 0x15e,
};

enum EDrawType {
    DT_None = 0,
};

class FName {
public:
    INT Index;
    FName() {}
    FName(EName N) : Index(N) {}
    INT GetIndex() const { return Index; }
};

struct FVector {
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
};

struct FBox {
    FVector Min, Max;
};

class UFunction;
class UStruct;
class UClass;
class UStaticMesh;
class USound;
class ULevel;
class AActor;
class APawn;
class ALevelInfo;
struct FFrame;

struct FStateFrame {
    BYTE unk_0[0x1c];
    QWORD ProbeMask;
};

class UObject {
public:
    virtual ~UObject();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = 0);

    INT Index;
    UObject *HashNext;
    FStateFrame *StateFrame;
    BYTE unk_10[0x24 - 0x10];
    UClass *Class;

    UBOOL IsProbing(FName ProbeName);
    UFunction *FindFunctionChecked(FName InName, UBOOL Global = 0);
};

typedef void (UObject::*Native)(FFrame &Stack, RESULT_DECL);
extern Native GNatives[];

class __declspec(novtable) FOutputDevice {
public:
    virtual void Serialize(const TCHAR *V, EName Event) = 0;
};

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

#define P_GET_BYTE(Var) BYTE Var = 0; Stack.Step(Stack.Object, &Var)
#define P_GET_OBJECT(Cls, Var) Cls *Var = 0; Stack.Step(Stack.Object, &Var)
#define P_GET_VECTOR(Var) FVector Var; Stack.Step(Stack.Object, &Var)
#define P_FINISH Stack.Code++

class FCollisionHash {
public:
    void AddActor(AActor *Actor);
};

void __stdcall FCollisionHash_RemoveActor(FCollisionHash *Hash, AActor *Actor);

class ULevel : public UObject {
public:
    BYTE unk_28[0x13c - 0x28];
    void *Model;
    BYTE unk_140[0x3a48 - 0x140];
    FCollisionHash *Hash;
    BYTE unk_3a4c[0x3a68 - 0x3a4c];
    BYTE ZoneDist[64 * 64];

    __declspec(noinline) UBOOL CheckSoundOcclusion(const FVector &Start, const FVector &End,
                                                   AActor *SoundMaker, BYTE OcclusionType);
    UBOOL SingleLineCheck(void *Hit, AActor *SourceActor, const FVector &End,
                          const FVector &Start, DWORD TraceFlags, void *Extent);
};

class AActor : public UObject {
public:
    BYTE unk_28[0x80 - 0x28];
    FVector Location;               // 0x80
    BYTE unk_8c[0xb0 - 0x8c];
    FVector DrawScale3D;            // 0xb0
    BYTE unk_bc[0xc8 - 0xbc];
    FBox Box;                       // 0xc8
    BYTE unk_e0[0x100 - 0xe0];
    UStaticMesh *StaticMesh;        // 0x100
    BYTE unk_104[0x134 - 0x104];
    INT unk_134;                    // 0x134
    BYTE unk_138[0x1a0 - 0x138];
    ALevelInfo *Level;              // 0x1a0
    ULevel *XLevel;                 // 0x1a4
    BYTE unk_1a8[0x1c4 - 0x1a8];
    INT *unk_1c4;                   // 0x1c4
    INT unk_1c8;                    // 0x1c8
    BYTE unk_1cc[0x250 - 0x1cc];
    DWORD unk_250;                  // 0x250
    BYTE unk_254[0x2d9 - 0x254];
    BYTE DrawType;                  // 0x2d9
    BYTE unk_2da[0x2e5 - 0x2da];
    BYTE SoundOcclusion;            // 0x2e5
    BYTE unk_2e6[0x2ec - 0x2e6];
    DWORD unk_2ec;                  // 0x2ec
    DWORD unk_2f0;                  // 0x2f0

    void Refresh_90de0();
    __declspec(noinline) void SetStaticMesh(UStaticMesh *NewStaticMesh);
    __declspec(noinline) void SetDrawType(EDrawType NewDrawType);
    __declspec(noinline) void SetDrawScale3D(FVector NewScale3D);

    void execSetStaticMesh(FFrame &Stack, RESULT_DECL);
    void execSetDrawType(FFrame &Stack, RESULT_DECL);
    void execSetDrawScale3D(FFrame &Stack, RESULT_DECL);
};

class APawn : public AActor {
public:
};

class AController : public AActor {
public:
    BYTE unk_2f4[0x2fc - 0x2f4];
    APawn *Pawn;                    // 0x2fc

    virtual void CheckHearSound(AActor *SoundMaker, INT Id, USound *S,
                                const FVector &Parameters, FLOAT Radius,
                                UBOOL bAttenuate, UBOOL bUnused);
    __declspec(noinline) UBOOL CanHearSound(const FVector &HearSource,
                                            AActor *SoundMaker, FLOAT Radius);
    __declspec(noinline) void eventAIHearSound(AActor *Actor, INT Id, USound *S,
                                               FVector SoundLocation, FVector Parameters,
                                               UBOOL Attenuate);
};

// AActor::execSetStaticMesh (RVA 0x124ea0)
void AActor::execSetStaticMesh(FFrame &Stack, RESULT_DECL)
{
    P_GET_OBJECT(UStaticMesh, NewStaticMesh);
    P_FINISH;
    SetStaticMesh(NewStaticMesh);
}

// AActor::execSetDrawType (RVA 0x124ee0)
void AActor::execSetDrawType(FFrame &Stack, RESULT_DECL)
{
    P_GET_BYTE(NewDrawType);
    P_FINISH;
    SetDrawType((EDrawType)NewDrawType);
}

// AActor::execSetDrawScale3D (RVA 0x124f20)
void AActor::execSetDrawScale3D(FFrame &Stack, RESULT_DECL)
{
    P_GET_VECTOR(NewScale3D);
    P_FINISH;
    SetDrawScale3D(NewScale3D);
}

// AController::CheckHearSound (RVA 0x124f70, vtable 0x306808 slot 78)
void AController::CheckHearSound(AActor *SoundMaker, INT Id, USound *S,
                                 const FVector &Parameters, FLOAT Radius,
                                 UBOOL bAttenuate, UBOOL bUnused)
{
    if (Pawn && IsProbing(NAME_AIHearSound) && CanHearSound(Pawn->Location, SoundMaker, Radius))
        eventAIHearSound(SoundMaker, Id, S, Pawn->Location, Parameters, bAttenuate);
}

#pragma pack(pop)

// ---------------------------------------------------------------------------
// Scaffolding for the link, not part of the unit.

void Escape(void *);
void UnnamedUse(AActor *Actor, INT Index);
FBox *UnnamedBox(AActor *Actor, FBox *Out);
FBox *UnnamedExpand(FBox *In, FBox *Out, FLOAT By);
void UnnamedInsert(FCollisionHash *Hash, AActor *Actor, INT X);

__declspec(noinline) void FCollisionHash::AddActor(AActor *Actor)
{
    FBox Tmp, Tmp2;
    if (!Actor || (Actor->unk_2f0 & 0x40))
        return;
    if (Actor->unk_134 > 0)
        FCollisionHash_RemoveActor(this, Actor);
    Actor->Box = *UnnamedBox(Actor, &Tmp);
    Actor->Box = *UnnamedExpand(&Actor->Box, &Tmp2, 4.2f);
    for (INT i = 0; i < Actor->unk_1c8; i++)
        UnnamedInsert(this, Actor, Actor->unk_1c4[i]);
}

__declspec(noinline) void AActor::Refresh_90de0()
{
    unk_134++;
    if (unk_250)
        for (INT i = 0; i < unk_1c8; i++)
            UnnamedUse(this, unk_1c4[i]);
}

void AActor::SetStaticMesh(UStaticMesh *NewStaticMesh)
{
    if ((unk_2f0 & 0x1000) && XLevel->Hash)
        FCollisionHash_RemoveActor(XLevel->Hash, this);
    StaticMesh = NewStaticMesh;
    if ((unk_2f0 & 0x1000) && XLevel->Hash)
        XLevel->Hash->AddActor(this);
    unk_2ec |= 4;
    Refresh_90de0();
}

void AActor::SetDrawType(EDrawType NewDrawType)
{
    if ((unk_2f0 & 0x1000) && XLevel->Hash)
        FCollisionHash_RemoveActor(XLevel->Hash, this);
    DrawType = (BYTE)NewDrawType;
    if ((unk_2f0 & 0x1000) && XLevel->Hash)
        XLevel->Hash->AddActor(this);
    unk_2ec |= 4;
}

void AActor::SetDrawScale3D(FVector NewScale3D)
{
    if ((unk_2f0 & 0x1000) && XLevel->Hash)
        FCollisionHash_RemoveActor(XLevel->Hash, this);
    DrawScale3D = NewScale3D;
    if ((unk_2f0 & 0x1000) && XLevel->Hash)
        XLevel->Hash->AddActor(this);
    unk_2ec |= 4;
}

class UClass : public UObject {
public:
    UClass *SuperField;
};

extern UClass *GPawnStaticClass;
extern void *GZeroExtent;
BYTE ModelFastLineCheck(void *Model, const FVector &Start, const FVector &End);
struct FPointRegion { BYTE Data[12]; };
FPointRegion *PointRegionQuery(void *Model, FPointRegion *Out, ALevelInfo *Level,
                               const FVector *Pos);
extern FLOAT GSoundRadiusScale;
extern DOUBLE GSoundAttenBase;
DOUBLE appPow(DOUBLE X, DOUBLE Y);

UBOOL ULevel::CheckSoundOcclusion(const FVector &Start, const FVector &End,
                                  AActor *SoundMaker, BYTE OcclusionType)
{
    BYTE Hit[0x38];
    switch (OcclusionType) {
    case 0:
    case 2:
        return ModelFastLineCheck(Model, Start, End);
    case 3:
        return SingleLineCheck(Hit, SoundMaker, Start, End, 0x286, GZeroExtent);
    default:
        return 1;
    }
}

UBOOL AController::CanHearSound(const FVector &HearSource, AActor *SoundMaker, FLOAT Radius)
{
    if (!XLevel->CheckSoundOcclusion(SoundMaker->Location, HearSource, SoundMaker,
                                     SoundMaker->SoundOcclusion)) {
        FPointRegion R1, R2;
        PointRegionQuery(XLevel->Model, &R1, Level, &HearSource);
        PointRegionQuery(XLevel->Model, &R2, Level, &SoundMaker->Location);
        AActor *A = 0;
        for (UClass *C = SoundMaker->Class; C; C = C->SuperField) {
            if (C == GPawnStaticClass) {
                A = SoundMaker;
                break;
            }
        }
        if (!R2.Data[0] && A) {
            FVector Alt = SoundMaker->Location;
            FPointRegion R3;
            PointRegionQuery(XLevel->Model, &R3, Level, &Alt);
            R2 = R3;
        }
        INT Dist = XLevel->ZoneDist[(R1.Data[0] << 6) + R2.Data[0]];
        Radius *= (FLOAT)appPow(GSoundAttenBase, (DOUBLE)(Dist * Dist));
    }
    FLOAT dx = HearSource.X - SoundMaker->Location.X;
    FLOAT dy = HearSource.Y - SoundMaker->Location.Y;
    FLOAT dz = HearSource.Z - SoundMaker->Location.Z;
    FLOAT MaxDist = GSoundRadiusScale * Radius;
    return (dx * dx + dy * dy + dz * dz) < (MaxDist * MaxDist);
}

void AController::eventAIHearSound(AActor *Actor, INT Id, USound *S, FVector SoundLocation,
                                   FVector Parameters, UBOOL Attenuate)
{
    struct AController_eventAIHearSound_Parms {
        AActor *Actor;
        INT Id;
        USound *S;
        FVector SoundLocation;
        FVector Parameters;
        UBOOL Attenuate;
    } Parms;
    if (StateFrame
        && !(StateFrame->ProbeMask & ((QWORD)1 << (NAME_AIHearSound - NAME_PROBEMIN))))
        return;
    Parms.Actor = Actor;
    Parms.Id = Id;
    Parms.S = S;
    Parms.SoundLocation = SoundLocation;
    Parms.Parameters = Parameters;
    Parms.Attenuate = Attenuate;
    ProcessEvent(FindFunctionChecked(NAME_AIHearSound), &Parms);
}

void Driver_124ea0(AActor *A, AActor *B, UStaticMesh *M)
{
    Native Fn = (Native)&AActor::execSetStaticMesh;
    Escape(&Fn);
    Escape(GNatives);
    A->SetStaticMesh(M);
    B->SetStaticMesh(M);
}

void Driver_124ee0(AActor *A, AActor *B, EDrawType D)
{
    Native Fn = (Native)&AActor::execSetDrawType;
    Escape(&Fn);
    Escape(GNatives);
    A->SetDrawType(D);
    B->SetDrawType(D);
}

void Driver_124f20(AActor *A, AActor *B, FVector V)
{
    Native Fn = (Native)&AActor::execSetDrawScale3D;
    Escape(&Fn);
    Escape(GNatives);
    A->SetDrawScale3D(V);
    B->SetDrawScale3D(V);
}

void Driver_124f70(AController *C, AActor *Maker, INT Id, USound *S,
                   const FVector &Params, FLOAT Radius, UBOOL bAtt, UBOOL bUn)
{
    AController Inst;
    Escape(&Inst);
    Escape((void *)(INT)C->CanHearSound(Params, Maker, Radius));
}
