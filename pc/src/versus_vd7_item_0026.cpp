// Work item 0026: Versus RVA 0x126bf0-0x1270d9
// APlayerController::execSetVoiceChatQuality, AActor::execMove,
// AActor::execSetLocation, AActor::execSetRelativeLocation, AActor::execSetRotation.

typedef unsigned char BYTE;
typedef unsigned short _WORD;
typedef unsigned short TCHAR;
typedef unsigned long DWORD;
typedef unsigned long BITFIELD;
typedef int INT;
typedef DWORD UBOOL;
typedef float FLOAT;

#define NULL 0
#define INDEX_NONE -1
#define RESULT_DECL void *const Result

enum EName {
    NAME_None = 0,
    ENGINE_ClientSetVoiceChatQuality = 0xfaf6e,
    ENGINE_ServerSetVoiceChatQuality = 0xfd28d
};

struct FName {
    INT Index;

    FName() {}
    FName(EName N) : Index(N) {}
    UBOOL operator==(const FName &Other) const { return Index == Other.Index; }
    UBOOL operator!=(const FName &Other) const { return Index != Other.Index; }
};

struct FVector {
    FLOAT X, Y, Z;

    FVector() {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector operator+(const FVector &V) const { return FVector(X + V.X, Y + V.Y, Z + V.Z); }
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FVector operator*(FLOAT Scale) const { return FVector(X * Scale, Y * Scale, Z * Scale); }
};

inline FVector operator*(FLOAT Scale, const FVector &V)
{
    return FVector(V.X * Scale, V.Y * Scale, V.Z * Scale);
}

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
    FCoords operator/(const FRotator &Rot) const;
};

struct FGlobalMath {
    FCoords UnitCoords;
};

extern FGlobalMath GMath;
__declspec(dllimport) extern const FVector GZeroVector;

template<class T> struct TArray {
    T  *Data;
    INT ArrayNum;
    INT ArrayMax;

    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return Data[i]; }
};

struct FGuid;
struct FFrame;
class UClass;
class UFunction;
class UStruct;
class UPrimitive;
class UMaterial;
class AActor;

class __declspec(novtable) FOutputDevice {
public:
    virtual void Serialize(const TCHAR *V, EName Event) = 0;
};

class FUnknown {
public:
    virtual DWORD __stdcall QueryInterface(const FGuid &RefIID, void **InterfacePtr);
    virtual DWORD __stdcall AddRef();
    virtual DWORD __stdcall Release();
};

class UObject : public FUnknown {
public:
    virtual ~UObject();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *UnusedResult = NULL);

    BYTE    unk_4[0x20];
    UClass *Class;

    UBOOL IsA(UClass *SomeBase) const;
    UFunction *FindFunctionChecked(FName InName, UBOOL Global = 0);
};

class UField : public UObject {
public:
    UField *SuperField;
};

class UClass : public UField {
public:
};

inline UBOOL UObject::IsA(UClass *SomeBase) const
{
    for (UClass *TempClass = Class; TempClass; TempClass = (UClass *)TempClass->SuperField)
        if (TempClass == SomeBase)
            return 1;
    return SomeBase == NULL;
}

template<class T> inline T *Cast(UObject *Src)
{
    return Src && Src->IsA(T::StaticClass()) ? (T *)Src : NULL;
}

typedef void (UObject::*Native)(FFrame &Stack, RESULT_DECL);
extern Native GNatives[];

struct FFrame : public FOutputDevice {
    UStruct *Node;
    UObject *Object;
    BYTE    *Code;
    BYTE    *Locals;

    void Step(UObject *Context, RESULT_DECL)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
};

#define P_GET_BYTE(Var) BYTE Var = 0; Stack.Step(Stack.Object, &Var)
#define P_GET_VECTOR(Var) FVector Var; Stack.Step(Stack.Object, &Var)
#define P_GET_ROTATOR(Var) FRotator Var; Stack.Step(Stack.Object, &Var)
#define P_FINISH Stack.Code++

struct FIteratorList {
    FIteratorList *Next;

    FIteratorList() {}
    FIteratorList(FIteratorList *InNext) : Next(InNext) {}
};

struct FIteratorActorList : public FIteratorList {
    AActor *Actor;

    FIteratorActorList() {}
    FIteratorActorList(FIteratorActorList *InNext, AActor *InActor)
        : FIteratorList(InNext), Actor(InActor) {}
};

struct FCheckResult : public FIteratorActorList {
    FVector     Location;
    FVector     Normal;
    UPrimitive *Primitive;
    FLOAT       Time;
    INT         Item;
    UMaterial  *Material;
    INT         unk_30;
    INT         unk_34;

    FCheckResult(FLOAT InTime, FCheckResult *InNext = NULL)
        : FIteratorActorList(InNext, NULL),
          Location(GZeroVector),
          Normal(GZeroVector),
          Primitive(NULL),
          Time(InTime),
          Item(INDEX_NONE),
          Material(NULL),
          unk_34(0)
    {}
};

class UAudioSubsystem : public UObject {
public:
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void VirtualSlot9();
    virtual void VirtualSlot10();
    virtual void VirtualSlot11();
    virtual void VirtualSlot12();
    virtual void VirtualSlot13();
    virtual void VirtualSlot14();
    virtual void VirtualSlot15();
    virtual void VirtualSlot16();
    virtual void VirtualSlot17();
    virtual void VirtualSlot18();
    virtual void VirtualSlot19();
    virtual void VirtualSlot20();
    virtual void VirtualSlot21();
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();
    virtual void VirtualSlot28();
    virtual void VirtualSlot29();
    virtual void VirtualSlot30();
    virtual void VirtualSlot31();
    virtual void VirtualSlot32();
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
    virtual void SetVoiceChatQuality(INT Quality);
};

class UEngine : public UObject {
public:
    BYTE             unk_28[0x0c];
    UAudioSubsystem *Audio;
};

class ULevel : public UObject {
public:
    BYTE             unk_28[0x44];
    TArray<AActor *> Actors;
    BYTE             unk_78[0x78];
    UEngine         *Engine;

    UBOOL MoveActor(AActor *Actor, const FVector &Delta, const FRotator &NewRotation,
                    FCheckResult &Hit, UBOOL Test = 0, UBOOL IgnorePawns = 0,
                    UBOOL bIgnoreBases = 0, UBOOL bNoFail = 0, UBOOL Extra = 0);
    UBOOL FarMoveActor(AActor *Actor, const FVector &DestLocation, UBOOL test = 0,
                       UBOOL bNoCheck = 0, UBOOL bAttachedMove = 0);
};

class AActor : public UObject {
public:
    BYTE     unk_28[0x58];
    FVector  Location;
    BYTE     unk_8c[0x18];
    FVector  RelativeLocation;
    BYTE     unk_b0[0x30];
    FRotator Rotation;
    BYTE     unk_ec[0x1c];
    AActor  *Base;
    BYTE     unk_10c[0x98];
    ULevel  *XLevel;
    BYTE     unk_1a8[0x110];
    FName    AttachmentBone;
    BYTE     unk_2bc[0x3c];

    ULevel *GetLevel() const { return XLevel; }

    void execMove(FFrame &Stack, RESULT_DECL);
    void execSetLocation(FFrame &Stack, RESULT_DECL);
    void execSetRelativeLocation(FFrame &Stack, RESULT_DECL);
    void execSetRotation(FFrame &Stack, RESULT_DECL);
};

class APlayerReplicationInfo : public AActor {
public:
    BYTE     unk_2f8[0x150];
    BITFIELD unk_448_0 : 14;
    BITFIELD bAdmin : 1;
    BITFIELD unk_448_15 : 17;
    BYTE     VoiceChatQuality;
};

class AGameReplicationInfo : public AActor {
public:
    BYTE unk_2f8[0x74];
    BYTE MaxVoiceChatQuality;
};

struct APlayerController_eventClientSetVoiceChatQuality_Parms {
    BYTE Quality;
};

struct APlayerController_eventServerSetVoiceChatQuality_Parms {
    BYTE Quality;
};

class APlayerController : public AActor {
public:
    BYTE                    unk_2f8[0x90];
    APlayerReplicationInfo *PlayerReplicationInfo;
    BYTE                    unk_38c[0x20c];
    AGameReplicationInfo   *GameReplicationInfo;

    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }

    void eventClientSetVoiceChatQuality(BYTE Quality)
    {
        APlayerController_eventClientSetVoiceChatQuality_Parms Parms;
        Parms.Quality = Quality;
        ProcessEvent(FindFunctionChecked(ENGINE_ClientSetVoiceChatQuality), &Parms);
    }

    void eventServerSetVoiceChatQuality(BYTE Quality)
    {
        APlayerController_eventServerSetVoiceChatQuality_Parms Parms;
        Parms.Quality = Quality;
        ProcessEvent(FindFunctionChecked(ENGINE_ServerSetVoiceChatQuality), &Parms);
    }

    void execSetVoiceChatQuality(FFrame &Stack, RESULT_DECL);
};

// APlayerController::execSetVoiceChatQuality (RVA 0x126bf0)
void APlayerController::execSetVoiceChatQuality(FFrame &Stack, RESULT_DECL)
{
    P_GET_BYTE(Quality);
    P_FINISH;

    if (PlayerReplicationInfo && PlayerReplicationInfo->bAdmin)
    {
        if (PlayerReplicationInfo->VoiceChatQuality != Quality)
        {
            GameReplicationInfo->MaxVoiceChatQuality = Quality;
            PlayerReplicationInfo->VoiceChatQuality = Quality;

            for (INT i = 0; i < XLevel->Actors.Num(); i++)
            {
                APlayerController *PC = Cast<APlayerController>(XLevel->Actors(i));
                if (PC != this)
                    PC->eventClientSetVoiceChatQuality(Quality);
            }
        }
    }
    else
    {
        if (GameReplicationInfo && GameReplicationInfo->MaxVoiceChatQuality < Quality)
            Quality = GameReplicationInfo->MaxVoiceChatQuality;

        if (PlayerReplicationInfo && PlayerReplicationInfo->VoiceChatQuality != Quality)
            eventServerSetVoiceChatQuality(Quality);
    }

    UAudioSubsystem *Audio = XLevel->Engine->Audio;
    if (Audio)
        Audio->SetVoiceChatQuality(Quality);
}

// AActor::execMove (RVA 0x126d60)
void AActor::execMove(FFrame &Stack, RESULT_DECL)
{
    P_GET_VECTOR(Delta);
    P_FINISH;

    FCheckResult Hit(1.f);
    *(UBOOL *)Result = GetLevel()->MoveActor(this, Delta, Rotation, Hit);
}

// AActor::execSetLocation (RVA 0x126e10)
void AActor::execSetLocation(FFrame &Stack, RESULT_DECL)
{
    P_GET_VECTOR(NewLocation);
    P_FINISH;

    *(UBOOL *)Result = GetLevel()->FarMoveActor(this, NewLocation);
}

// AActor::execSetRelativeLocation (RVA 0x126e70)
void AActor::execSetRelativeLocation(FFrame &Stack, RESULT_DECL)
{
    P_GET_VECTOR(NewLocation);
    P_FINISH;

    if (AttachmentBone != NAME_None)
    {
        RelativeLocation = NewLocation;
        *(UBOOL *)Result = 1;
        return;
    }

    if (Base)
    {
        FCoords C = GMath.UnitCoords / Base->Rotation;
        NewLocation = Base->Location + NewLocation.X * C.XAxis + NewLocation.Y * C.YAxis + NewLocation.Z * C.ZAxis;
        *(UBOOL *)Result = GetLevel()->FarMoveActor(this, NewLocation, 0, 0, 1);
        if (Base)
            RelativeLocation = Location - Base->Location;
    }
}

// AActor::execSetRotation (RVA 0x127030)
void AActor::execSetRotation(FFrame &Stack, RESULT_DECL)
{
    P_GET_ROTATOR(NewRotation);
    P_FINISH;

    FCheckResult Hit(1.f);
    *(UBOOL *)Result = GetLevel()->MoveActor(this, GZeroVector, NewRotation, Hit);
}
