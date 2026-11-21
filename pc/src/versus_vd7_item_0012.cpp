// Work item 0012: Versus RVA 0x1251b0-0x125636, 3 functions, 1145 bytes.
//   0x1251b0 ASPlayerController::CheckHearSound
//   0x125270 AActor::execTraceBone
//   0x125590 AActor::execGetRainVolume
// Built with VC7.0 /GL and linked with /LTCG (/O2 /Gy).

typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

#define RESULT_DECL void *const Result

class UObject;
class UClass;
class UProperty;
class UPrimitive;
class UMaterial;
class USound;
class UFunction;
class AActor;
class AERainVolume;
class UERainPrimitive;
class ULevel;
struct FFrame;

struct FName {
    INT Index;
    FName() {}
    FName(INT InIndex) : Index(InIndex) {}
};

class FVector {
public:
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector operator*(const FVector &V) const { return FVector(X * V.X, Y * V.Y, Z * V.Z); }
};

class FPlane : public FVector {
public:
    FLOAT W;
    FPlane() {}
    FPlane(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW) : FVector(InX, InY, InZ), W(InW) {}
};

class FMatrix {
public:
    FPlane XPlane, YPlane, ZPlane, WPlane;
    FPlane TransformFPlane(const FPlane &P) const;
    FVector TransformFVector(const FVector &V) const
    {
        return TransformFPlane(FPlane(V.X, V.Y, V.Z, 1.f));
    }
};

struct FRainBounds {
    FVector Min, Max;
    FRainBounds() { Min.X = 1.f; Max.X = 0.f; }
    FRainBounds(const FRainBounds &Other)
    {
        Min.X = Other.Min.X; Min.Y = Other.Min.Y; Min.Z = Other.Min.Z;
        Max.X = Other.Max.X; Max.Y = Other.Max.Y; Max.Z = Other.Max.Z;
    }
};

class FArray {
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Num() const { return ArrayNum; }
};

template <class T> class TArray : public FArray {
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    const T &operator()(INT i) const { return ((const T *)Data)[i]; }
};

typedef void (UObject::*Native)(FFrame &Stack, RESULT_DECL);
extern Native GNatives[];
extern BYTE *GPropAddr;
extern UObject *GPropObject;
extern UProperty *GProperty;

class UField {
public:
    BYTE unk_00[0x28];
    UField *SuperField; // 0x28
};

class UClass : public UField {
};

class UObject {
public:
    virtual void Slot00();
    virtual void Slot01();
    virtual void Slot02();
    virtual void Slot03();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *UnusedResult = 0); // +0x10
    virtual void Slot05(); virtual void Slot06(); virtual void Slot07();
    virtual void Slot08(); virtual void Slot09(); virtual void Slot10(); virtual void Slot11();
    virtual void Slot12(); virtual void Slot13(); virtual void Slot14(); virtual void Slot15();
    virtual void Slot16(); virtual void Slot17(); virtual void Slot18(); virtual void Slot19();
    virtual void Slot20();
    virtual void NetDirty(UProperty *Property); // +0x54

    BYTE unk_04[0x20];
    UClass *Class; // 0x24

    UFunction *FindFunctionChecked(FName InName, INT Global = 0);

    UBOOL IsA(UClass *SomeBase) const
    {
        for (UField *TempClass = Class; TempClass; TempClass = TempClass->SuperField)
            if (TempClass == SomeBase)
                return 1;
        return 0;
    }
};

template <class T> inline T *Cast(UObject *Src)
{
    return Src && Src->IsA(T::StaticClass()) ? (T *)Src : 0;
}

class UPrimitive : public UObject {
public:
    virtual void Slot22();
    virtual void Slot23();
    virtual FRainBounds GetRainBounds(AActor *Owner); // slot 24
};

struct FBspNode {
    BYTE unk_00[0x2c];
    INT iSurf;         // 0x2c
    BYTE unk_30[0x2c]; // total 0x5c
};

struct FBspSurf {
    BYTE unk_00[0x14];
    DWORD PolyFlags;   // 0x14
    BYTE unk_18[0x14]; // total 0x2c
};

class UModel : public UPrimitive {
public:
    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }

    BYTE unk_28[0x2c];
    TArray<FBspNode> Nodes; // 0x54
    BYTE unk_60[0x34];
    TArray<FBspSurf> Surfs; // 0x94
};

struct FCheckResult {
    FCheckResult *Next;
    AActor *Actor;
    FVector Location;
    FVector Normal;
    UPrimitive *Primitive;
    FLOAT Time;
    INT Item;
    UMaterial *Material;
    FName BoneName;
    INT unk_34;
};

struct FFrame {
    void *VfTable;
    void *Node;      // +0x04
    UObject *Object; // +0x08
    BYTE *Code;      // +0x0c

    __forceinline void Step(UObject *Context, RESULT_DECL)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
};

#define P_GET_UBOOL(var) \
    UBOOL var = 0; Stack.Step(Stack.Object, &var);
#define P_GET_UBOOL_REF(var) \
    UBOOL var##T = 0; GPropAddr = 0; Stack.Step(Stack.Object, &var##T); \
    if (GPropObject) GPropObject->NetDirty(GProperty); \
    UBOOL *var = GPropAddr ? (UBOOL *)GPropAddr : &var##T;
#define P_GET_NAME_REF(var) \
    FName var##T(0); GPropAddr = 0; Stack.Step(Stack.Object, &var##T); \
    if (GPropObject) GPropObject->NetDirty(GProperty); \
    FName *var = GPropAddr ? (FName *)GPropAddr : &var##T;
#define P_GET_VECTOR(var) \
    FVector var; Stack.Step(Stack.Object, &var);
#define P_GET_VECTOR_OPTX(var, def) \
    FVector var = def; Stack.Step(Stack.Object, &var);
#define P_GET_VECTOR_REF(var) \
    FVector var##T; GPropAddr = 0; Stack.Step(Stack.Object, &var##T); \
    if (GPropObject) GPropObject->NetDirty(GProperty); \
    FVector *var = GPropAddr ? (FVector *)GPropAddr : &var##T;
#define P_GET_OBJECT_REF(cls, var) \
    cls *var##T = 0; GPropAddr = 0; Stack.Step(Stack.Object, &var##T); \
    if (GPropObject) GPropObject->NetDirty(GProperty); \
    cls **var = GPropAddr ? (cls **)GPropAddr : &var##T;
#define P_FINISH Stack.Code++;

class ULevel {
public:
    BYTE unk_0000[0x4a68];
    TArray<AERainVolume *> RainVolumes; // 0x4a68
};

class AActor : public UObject {
public:
    virtual void Slot22(); virtual void Slot23(); virtual void Slot24(); virtual void Slot25();
    virtual void Slot26(); virtual void Slot27(); virtual void Slot28(); virtual void Slot29();
    virtual void Slot30(); virtual void Slot31(); virtual void Slot32(); virtual void Slot33();
    virtual void Slot34(); virtual void Slot35(); virtual void Slot36(); virtual void Slot37();
    virtual void Slot38(); virtual void Slot39(); virtual void Slot40(); virtual void Slot41();
    virtual void Slot42(); virtual void Slot43();
    virtual UPrimitive *GetPrimitive(); // slot 44 (+0xb0)
    virtual void Slot45(); virtual void Slot46(); virtual void Slot47(); virtual void Slot48();
    virtual void Slot49(); virtual void Slot50(); virtual void Slot51(); virtual void Slot52();
    virtual void Slot53(); virtual void Slot54(); virtual void Slot55(); virtual void Slot56();
    virtual void Slot57(); virtual void Slot58(); virtual void Slot59(); virtual void Slot60();
    virtual void Slot61(); virtual void Slot62(); virtual void Slot63(); virtual void Slot64();
    virtual void Slot65(); virtual void Slot66(); virtual void Slot67(); virtual void Slot68();
    virtual void Slot69(); virtual void Slot70(); virtual void Slot71(); virtual void Slot72();
    virtual void Slot73(); virtual void Slot74(); virtual void Slot75(); virtual void Slot76();
    virtual void Slot77();

    BYTE unk_28[0x58];
    FVector Location;  // 0x80
    BYTE unk_8c[0x118];
    ULevel *XLevel;    // 0x1a4

    FMatrix WorldToLocal();
    FCheckResult TraceBone(FVector TraceEnd, FVector TraceStart,
                           bool bTraceActors, bool bGetMaterial);

    void execTraceBone(FFrame &Stack, RESULT_DECL);
    void execGetRainVolume(FFrame &Stack, RESULT_DECL);
};

class AERainVolume : public AActor {
public:
    BYTE unk_1a8[0x180];
    FRainBounds Bounds;
};

class UERainPrimitive : public UPrimitive {
public:
    BYTE unk_28[0x28];
    AERainVolume *Volume; // 0x50
    bool PointInside(const FVector &Point);
};

class ASPlayerController : public AActor {
public:
    ASPlayerController();
    virtual void CheckHearSound(AActor *SoundMaker, INT Id, USound *Sound,
                                const FVector &Parameters, FLOAT Radius,
                                UBOOL Attenuate, UBOOL Occluded); // slot 78 (+0x138)
    virtual void UpdateViewTarget(); // slot 79 (+0x13c)

    BYTE unk_1a8[0x35c];
    AActor *ViewTarget; // 0x504

    UBOOL HearSoundCheck(AActor *SoundMaker, FVector &ViewLocation, FLOAT Radius);
    void eventClientHearSound(AActor *Actor, INT Id, USound *S, FVector SoundLocation,
                              FVector Parameters, UBOOL Attenuate, UBOOL Occluded);
};

// ASPlayerController::CheckHearSound (RVA 0x1251b0)
// Updates the view target, tests whether the sound is audible, and forwards to ClientHearSound.
void ASPlayerController::CheckHearSound(AActor *SoundMaker, INT Id, USound *Sound,
                                        const FVector &Parameters, FLOAT Radius,
                                        UBOOL Attenuate, UBOOL Occluded)
{
    FVector SoundLocation = SoundMaker->Location;
    UpdateViewTarget();
    if (HearSoundCheck(SoundMaker, ViewTarget->Location, Radius) || !Attenuate) {
        eventClientHearSound(
            SoundMaker,
            Id,
            Sound,
            SoundLocation,
            Parameters * FVector(1000.f, 1.f, 1000.f),
            Attenuate,
            Occluded);
    }
}

// AActor::execTraceBone (RVA 0x125270)
// Script native wrapper around AActor::TraceBone.
void AActor::execTraceBone(FFrame &Stack, RESULT_DECL)
{
    P_GET_UBOOL_REF(bHitFlag);
    P_GET_NAME_REF(HitBone);
    P_GET_VECTOR_REF(HitLocation);
    P_GET_VECTOR_REF(HitNormal);
    P_GET_VECTOR(TraceEnd);
    P_GET_VECTOR_OPTX(TraceStart, Location);
    P_GET_OBJECT_REF(UMaterial, HitMaterial);
    P_GET_UBOOL(bTraceActors);
    P_FINISH;

    FCheckResult Hit;
    Hit = TraceBone(TraceEnd, TraceStart, bTraceActors != 0, HitMaterial != 0);
    *(AActor **)Result = Hit.Actor;
    *HitLocation = Hit.Location;
    *HitNormal = Hit.Normal;
    *HitBone = Hit.BoneName;

    UModel *Model = Cast<UModel>(Hit.Primitive);
    if (Model && (Model->Surfs(Model->Nodes(Hit.Item).iSurf).PolyFlags & 0x80))
        *bHitFlag = 1;
    else
        *bHitFlag = 0;

    if (HitMaterial)
        *HitMaterial = Hit.Material;
}

// AActor::execGetRainVolume (RVA 0x125590)
// Returns the first AERainVolume in XLevel->RainVolumes containing Point, or NULL.
void AActor::execGetRainVolume(FFrame &Stack, RESULT_DECL)
{
    P_GET_VECTOR(Point);
    P_FINISH;

    INT Num = XLevel->RainVolumes.Num();
    for (INT i = 0; i < Num; i++) {
        if (XLevel->RainVolumes(i) &&
            ((UERainPrimitive *)XLevel->RainVolumes(i)->GetPrimitive())->PointInside(Point)) {
            *(AERainVolume **)Result = XLevel->RainVolumes(i);
            return;
        }
    }
    *(AERainVolume **)Result = 0;
}

// ---------------------------------------------------------------------------
// Scaffolding for the link, not part of the unit.
// Stand-ins for LTCG callees in other objects so the linker assigns them
// retail's register conventions, plus root drivers for try_ltcg.py.
// ---------------------------------------------------------------------------

UBOOL FPointBoxIntersection(const FVector &Point, const FRainBounds &Box);
__declspec(noinline) bool UERainPrimitive::PointInside(const FVector &Point)
{
    FVector Local = Volume->WorldToLocal().TransformFVector(Point);
    return FPointBoxIntersection(Local, GetRainBounds(0)) ? true : false;
}

extern INT GTraceCheckHelper(AActor *Self, DWORD Flags, FVector End,
                             FVector Start, FCheckResult &Hit);
extern INT GTraceCheckHelper2(INT A, INT B, INT C, INT D, bool *GetMat);
extern INT GLoopN;
extern FCheckResult GHitCopy;
__declspec(noinline) FCheckResult AActor::TraceBone(FVector TraceEnd, FVector TraceStart,
                                                    bool bTraceActors, bool bGetMaterial)
{
    DWORD TraceFlags = bTraceActors ? 0x60097 : 0x40097;
    if (bGetMaterial)
        TraceFlags |= 0x1000;
    FCheckResult Hit;
    INT A = 1, B = 2, C = 3, D = 4;
    for (INT i = 0; i < GLoopN; i++) {
        A += GTraceCheckHelper2(A, B, C, D, &bGetMaterial);
        B += GTraceCheckHelper2(B, C, D, A, &bGetMaterial);
        C += GTraceCheckHelper2(C, D, A, B, &bGetMaterial);
        D += GTraceCheckHelper2(D, A, B, C, &bGetMaterial);
        GTraceCheckHelper(this, TraceFlags, TraceEnd, TraceStart, Hit);
        GHitCopy = Hit;
    }
    Hit.Item = A + B + C + D;
    return Hit;
}

extern UBOOL GHearHelper1(FVector *Loc, AActor *Maker, ULevel *Lvl);
extern INT GHearHelper2(ULevel *Level, FVector *Loc);
extern UBOOL GHearHelper3(AActor *Maker, ULevel *Lvl, FVector *ViewLoc, FLOAT Radius);
__declspec(noinline) UBOOL ASPlayerController::HearSoundCheck(AActor *SoundMaker,
                                                              FVector &ViewLocation,
                                                              FLOAT Radius)
{
    FVector *MakerLoc = &SoundMaker->Location;
    if (GHearHelper1(MakerLoc, SoundMaker, XLevel))
        return 1;
    while (GHearHelper2(XLevel, MakerLoc))
        GHearHelper2(XLevel, MakerLoc);
    return GHearHelper3(SoundMaker, XLevel, &ViewLocation, Radius);
}

__declspec(noinline) void ASPlayerController::eventClientHearSound(
    AActor *Actor, INT Id, USound *S, FVector SoundLocation,
    FVector Parameters, UBOOL Attenuate, UBOOL Occluded)
{
    struct FClientHearSoundParms {
        AActor *Actor;
        INT Id;
        USound *S;
        FVector SoundLocation;
        FVector Parameters;
        UBOOL Attenuate;
        UBOOL Occluded;
    } Parms;
    Parms.Actor = Actor;
    Parms.Id = Id;
    Parms.S = S;
    Parms.SoundLocation = SoundLocation;
    Parms.Parameters = Parameters;
    Parms.Attenuate = Attenuate;
    Parms.Occluded = Occluded;
    ProcessEvent(FindFunctionChecked(FName(0xf25)), &Parms);
}

inline void *operator new(unsigned int, void *Mem) { return Mem; }
ASPlayerController::ASPlayerController() {}

void Driver_1251b0(void *P)
{
    new(P) ASPlayerController;
}

void Driver_125270(void *Out)
{
    *(void (AActor::**)(FFrame &, RESULT_DECL))Out = &AActor::execTraceBone;
}

void Driver_125590(void *Out)
{
    *(void (AActor::**)(FFrame &, RESULT_DECL))Out = &AActor::execGetRainVolume;
}
