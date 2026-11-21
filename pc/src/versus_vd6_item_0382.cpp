// Work item 0382: Versus RVA 0x11ac30 (ULevel::SpawnPlayActor) and 0x11aeb0 (ULevel::CheckSlice).

typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned int UINT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

extern "C" __declspec(dllimport) TCHAR* __cdecl wcscat(TCHAR* Dest, const TCHAR* Src);
extern "C" __declspec(dllimport) UINT __cdecl wcslen(const TCHAR* Str);
extern "C" void* __cdecl appMemcpy(void* Dest, const void* Src, INT Count);

enum ENetRole
{
    ROLE_None = 0,
    ROLE_DumbProxy = 1,
    ROLE_SimulatedProxy = 2,
    ROLE_AutonomousProxy = 3,
    ROLE_Authority = 4,
};

enum EName
{
    ENGINE_TravelPreAccept = 0xa47,
    ENGINE_TravelPostAccept = 0xa48,
    ENGINE_Login = 0xd03,
    ENGINE_PostLogin = 0xd14,
    ENGINE_InitInputSystem = 0xf2c,
};

enum ETraceFlags
{
    TRACE_World = 0x86,
};

struct FName
{
    INT Index;
    FName() {}
    FName(EName N) : Index(N) {}
};

struct FVector
{
    FLOAT X, Y, Z;

    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector& V) : X(V.X), Y(V.Y), Z(V.Z) {}

    FVector operator+(const FVector& V) const
    {
        return FVector(X + V.X, Y + V.Y, Z + V.Z);
    }
    FVector operator-(const FVector& V) const
    {
        return FVector(X - V.X, Y - V.Y, Z - V.Z);
    }
    FVector operator*(FLOAT Scale) const
    {
        return FVector(X * Scale, Y * Scale, Z * Scale);
    }
    FVector operator+=(const FVector& V)
    {
        X += V.X; Y += V.Y; Z += V.Z;
        return *this;
    }
    FVector operator-=(const FVector& V)
    {
        X -= V.X; Y -= V.Y; Z -= V.Z;
        return *this;
    }
    UBOOL operator==(const FVector& V) const
    {
        return X == V.X && Y == V.Y && Z == V.Z;
    }
};

extern const FVector& GZeroVector;

class AActor;
class UPrimitive;
class UMaterial;

struct FCheckResult
{
    FCheckResult* Next;    // 0x00
    AActor* Actor;         // 0x04
    FVector Location;      // 0x08
    FVector Normal;        // 0x14
    UPrimitive* Primitive; // 0x20
    FLOAT Time;            // 0x24
    INT Item;              // 0x28
    UMaterial* Material;   // 0x2c
    DWORD Extra[2];        // 0x30..0x37 (total 0x38 bytes)

    FCheckResult() {}
    FCheckResult(FLOAT InTime)
        : Location(GZeroVector), Normal(GZeroVector)
    {
        Actor = 0;
        Time = InTime;
    }
};

class FMalloc
{
public:
    virtual void* Malloc(DWORD Count, const TCHAR* Tag) = 0;
    virtual void* Realloc(void* Original, DWORD Count, const TCHAR* Tag) = 0;
    virtual void Free(void* Original) = 0;
};
extern FMalloc* GMalloc;

class FString
{
public:
    TCHAR* Data;
    INT ArrayNum;
    INT ArrayMax;

    FString() : Data(0), ArrayNum(0), ArrayMax(0) {}
    FString(const TCHAR* In);
    FString(const FString& Other);
    ~FString();
    FString& operator=(const TCHAR* Other);
    FString& operator=(const FString& Other);

    const TCHAR* operator*() const
    {
        return ArrayNum ? Data : L"";
    }
};

// External definitions for literals that retail keeps in writable .data.
extern const TCHAR GEmptyString_11ac30[];
extern const TCHAR GEmptyInit_11ac30[];
extern const TCHAR GQuestionMark_11ac30[];

template<class T>
class TArray
{
public:
    T* Data;
    INT ArrayNum;
    INT ArrayMax;

    INT Num() const { return ArrayNum; }
    T& operator()(INT i) { return Data[i]; }
    const T& operator()(INT i) const { return Data[i]; }
};

struct FURL
{
    FString Protocol;      // 0x00
    FString Host;          // 0x0c
    INT Port;              // 0x18
    FString Map;           // 0x1c
    TArray<FString> Op;    // 0x28
    FString Portal;        // 0x34
    INT Valid;             // 0x40
};

class UClass;
class UFunction;

class UObject
{
public:
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void ProcessEvent(UFunction* Function, void* Parms, void* Result = 0);

    DWORD Pad04[8];        // 0x04..0x23
    UClass* Class;         // 0x24

    UFunction* FindFunctionChecked(FName InName, INT Global = 0);
    UBOOL IsA(UClass* SomeBase) const;
};

class UClass : public UObject
{
public:
    UClass* SuperField;    // 0x28
};

inline UBOOL UObject::IsA(UClass* SomeBase) const
{
    for (UClass* TempClass = Class; TempClass; TempClass = TempClass->SuperField)
        if (TempClass == SomeBase)
            return 1;
    return 0;
}

template<class T>
inline T* Cast(UObject* Src)
{
    return Src && Src->IsA(T::StaticClass()) ? (T*)Src : 0;
}

class APlayerController;

class UPlayer : public UObject
{
public:
    DWORD Pad28[2];            // 0x28..0x2f
    APlayerController* Actor;  // 0x30
};

class UNetConnection : public UPlayer
{
public:
    static UClass PrivateStaticClass;
    static UClass* StaticClass() { return &PrivateStaticClass; }
};

class UViewport : public UPlayer
{
public:
    static UClass PrivateStaticClass;
    static UClass* StaticClass() { return &PrivateStaticClass; }
};

class AActor : public UObject
{
public:
    BYTE Pad28[0x2b5];     // 0x28..0x2dc
    BYTE RemoteRole;       // 0x2dd
    BYTE Role;             // 0x2de
    BYTE Pad2df[0x1d];     // 0x2df..0x2fb
    AActor* Pawn;          // 0x2fc

    void eventTravelPreAccept()
    {
        ProcessEvent(FindFunctionChecked(ENGINE_TravelPreAccept), 0);
    }
    void eventTravelPostAccept()
    {
        ProcessEvent(FindFunctionChecked(ENGINE_TravelPostAccept), 0);
    }
};

class APlayerController : public AActor
{
public:
    BYTE Pad300[0x1a4];    // 0x300..0x4a3
    UPlayer* Player;       // 0x4a4
    BYTE Pad4a8[0x48];     // 0x4a8..0x4ef
    DWORD ShowFlags;       // 0x4f0
    DWORD Pad4f4[2];       // 0x4f4..0x4fb
    INT RendMap;           // 0x4fc

    void eventInitInputSystem()
    {
        ProcessEvent(FindFunctionChecked(ENGINE_InitInputSystem), 0);
    }
};

struct AGameInfo_eventLogin_Parms
{
    FString Portal;
    FString Options;
    FString Error;
    APlayerController* ReturnValue;
};

struct AGameInfo_eventPostLogin_Parms
{
    APlayerController* NewPlayer;
};

class AGameInfo : public AActor
{
public:
    APlayerController* eventLogin(const FString& Portal, const FString& Options, FString& Error);
    void eventPostLogin(APlayerController* NewPlayer)
    {
        AGameInfo_eventPostLogin_Parms Parms;
        Parms.NewPlayer = NewPlayer;
        ProcessEvent(FindFunctionChecked(ENGINE_PostLogin), &Parms);
    }
};

class ALevelInfo : public AActor
{
public:
    BYTE Pad300[0x1dc];    // 0x300..0x4db
    AGameInfo* Game;       // 0x4dc
};

struct FMemStack
{
    BYTE* Top;
    BYTE* End;
    void* TopChunk;
    void* TopMark;

    void FreeChunks(void* NewTopChunk);
};
extern FMemStack GMem;

class ULevel : public UObject
{
public:
    DWORD Pad28;           // 0x28
    TArray<AActor*> Actors;// 0x2c

    ALevelInfo* GetLevelInfo() const
    {
        return (ALevelInfo*)Actors.Data[0];
    }

    APlayerController* SpawnPlayActor(UPlayer* Player, ENetRole RemoteRole, const FURL& URL, FString& Error);
    INT CheckSlice(FVector& Adjusted, const FVector& Extent, INT& bKeepTrying);
    UBOOL SinglePointCheck(FCheckResult& Hit, const FVector& Location, const FVector& Extent, DWORD ExtraNodeFlags, ALevelInfo* Level);
    UBOOL SingleLineCheck(FCheckResult& Hit, AActor* SourceActor, const FVector& End, const FVector& Start, DWORD TraceFlags, const FVector& Extent);
};

extern FCheckResult* __fastcall MultiPointCheck_Helper(ALevelInfo* Level, FMemStack* Mem, ULevel* This, const FVector& Location, const FVector& Extent, DWORD ExtraNodeFlags, UBOOL bActors, UBOOL bWorld);
extern FCheckResult* __fastcall MultiLineCheck_Helper(ULevel* This, FMemStack* Mem, const FVector& End, const FVector& Start, const FVector& Extent, ALevelInfo* Level, DWORD TraceFlags, AActor* SourceActor);

// RVA 0x11ac30
APlayerController* ULevel::SpawnPlayActor(UPlayer* Player, ENetRole RemoteRole, const FURL& URL, FString& Error)
{
    Error = GEmptyString_11ac30;

    // Result only used by stripped debugf in non-final builds.
    Cast<UNetConnection>(Player);

    TCHAR Options[1024] = { GEmptyInit_11ac30[0] };
    for (INT i = 0; i < URL.Op.Num(); i++)
    {
        wcscat(Options, GQuestionMark_11ac30);
        wcscat(Options, *URL.Op(i));
    }

    APlayerController* Actor = GetLevelInfo()->Game->eventLogin(*URL.Portal, Options, Error);
    if (!Actor)
        return 0;

    if (Player->Actor)
        Player->Actor->Player = 0;
    Actor->Player = Player;
    Player->Actor = Actor;
    if (Player->IsA(UViewport::StaticClass()))
        Actor->eventInitInputSystem();

    Actor->RemoteRole = (BYTE)RemoteRole;
    Actor->Role = ROLE_Authority;
    Actor->ShowFlags = 0x4000;
    Actor->RendMap = 5;

    GetLevelInfo()->Game->eventPostLogin(Actor);
    if (Actor->Pawn)
    {
        Actor->eventTravelPreAccept();
        Actor->Pawn->eventTravelPreAccept();
        Actor->eventTravelPostAccept();
    }
    return Actor;
}

// RVA 0x11aeb0
INT ULevel::CheckSlice(FVector& Adjusted, const FVector& Extent, INT& bKeepTrying)
{
    FCheckResult Hit(1.f);

    FVector SliceExtent = Extent;
    SliceExtent.Z = 1.f;
    bKeepTrying = 0;
    if (!SinglePointCheck(Hit, Adjusted, SliceExtent, 0, GetLevelInfo()))
    {
        FVector ZExtent(0.f, 0.f, Extent.Z);
        SingleLineCheck(Hit, 0, Adjusted - ZExtent * 2.f, Adjusted, TRACE_World, SliceExtent);
        FVector Normal = Hit.Normal;
        Normal.Z = 0.f;

        if (!Hit.Actor || Hit.Time > 0.5f)
        {
            if (!Hit.Actor)
            {
                Adjusted = Adjusted - ZExtent;
            }
            else
            {
                Adjusted -= ZExtent * (2.f * Hit.Time - 1.f);
                Adjusted.Z += 1.f;
            }

            if (!SinglePointCheck(Hit, Adjusted, Extent, 0, GetLevelInfo()))
            {
                SingleLineCheck(Hit, 0, Adjusted + ZExtent, Adjusted, TRACE_World, Extent);
                if (!Hit.Actor)
                    Adjusted = Adjusted + ZExtent;
                else
                    Adjusted = Hit.Location;
                return 1;
            }
            else
            {
                Adjusted = Adjusted + Normal * Extent.X;
                return !SinglePointCheck(Hit, Adjusted, Extent, 0, GetLevelInfo());
            }
        }
        else
        {
            Adjusted += ZExtent * (2.f * (0.5f - Hit.Time));
            Adjusted.Z += 1.f;
            if (!SinglePointCheck(Hit, Adjusted, Extent, 0, GetLevelInfo()))
                return 1;
            Adjusted += Normal * Extent.X;
            return !SinglePointCheck(Hit, Adjusted, Extent, 0, GetLevelInfo());
        }
    }

    bKeepTrying = 1;
    return 0;
}

// Scaffolding for the LTCG link (callees with custom calling conventions + drivers).
FString& FString::operator=(const TCHAR* Other)
{
    if (Other != Data)
    {
        if (*Other == 0)
        {
            if (Data)
            {
                ArrayNum = 0;
                ArrayMax = 0;
                GMalloc->Free(Data);
                Data = 0;
            }
        }
        else
        {
            if (Data == 0)
            {
                ArrayMax = ArrayNum = (INT)wcslen(Other) + 1;
                Data = (TCHAR*)GMalloc->Malloc(ArrayMax * sizeof(TCHAR), L"FString::=");
            }
            else
            {
                ArrayMax = ArrayNum = (INT)wcslen(Other) + 1;
                Data = (TCHAR*)GMalloc->Realloc(Data, ArrayMax * sizeof(TCHAR), L"FArray");
            }
            appMemcpy(Data, Other, ArrayNum * sizeof(TCHAR));
        }
    }
    return *this;
}

APlayerController* AGameInfo::eventLogin(const FString& Portal, const FString& Options, FString& Error)
{
    AGameInfo_eventLogin_Parms Parms;
    Parms.Portal = Portal;
    Parms.Options = Options;
    Parms.Error = Error;
    Parms.ReturnValue = 0;
    ProcessEvent(FindFunctionChecked(ENGINE_Login), &Parms);
    Error = Parms.Error;
    return Parms.ReturnValue;
}

UBOOL ULevel::SinglePointCheck(FCheckResult& Hit, const FVector& Location, const FVector& Extent, DWORD ExtraNodeFlags, ALevelInfo* Level)
{
    BYTE* SavedTop = GMem.Top;
    void* SavedChunk = GMem.TopChunk;
    FCheckResult* Hits = MultiPointCheck_Helper(Level, &GMem, this, Location, Extent, ExtraNodeFlags, 1, 1);
    if (!Hits)
    {
        if (SavedChunk != GMem.TopChunk)
            GMem.FreeChunks(SavedChunk);
        GMem.Top = SavedTop;
        return 0;
    }
    Hit = *Hits;
    if (SavedChunk != GMem.TopChunk)
        GMem.FreeChunks(SavedChunk);
    GMem.Top = SavedTop;
    return 1;
}

UBOOL ULevel::SingleLineCheck(FCheckResult& Hit, AActor* SourceActor, const FVector& End, const FVector& Start, DWORD TraceFlags, const FVector& Extent)
{
    BYTE* SavedTop = GMem.Top;
    void* SavedChunk = GMem.TopChunk;
    FCheckResult* Hits = MultiLineCheck_Helper(this, &GMem, End, Start, Extent, GetLevelInfo(), TraceFlags, SourceActor);
    if (Hits)
    {
        Hit = *Hits;
    }
    else
    {
        Hit.Time = 1.f;
        Hit.Actor = 0;
    }
    if (SavedChunk != GMem.TopChunk)
        GMem.FreeChunks(SavedChunk);
    GMem.Top = SavedTop;
    return Hits == 0;
}

void Escape(void*);

APlayerController* Driver_11ac30(ULevel* L, UPlayer* P, ENetRole R, const FURL& U, FString& E, AGameInfo* G, const TCHAR* S)
{
    Escape(&GMalloc);
    Escape((void*)GEmptyString_11ac30);
    Escape((void*)GEmptyInit_11ac30);
    Escape((void*)GQuestionMark_11ac30);
    Escape(&UNetConnection::PrivateStaticClass);
    Escape(&UViewport::PrivateStaticClass);
    E = S;
    G->eventLogin(E, E, E);
    APlayerController* A1 = L->SpawnPlayActor(P, ROLE_SimulatedProxy, U, E);
    APlayerController* A2 = L->SpawnPlayActor(P, ROLE_AutonomousProxy, U, E);
    APlayerController* A3 = L->SpawnPlayActor(P, R, U, E);
    return A1 ? A1 : (A2 ? A2 : A3);
}

typedef UBOOL (ULevel::*SingleLineCheckFn)(FCheckResult&, AActor*, const FVector&, const FVector&, DWORD, const FVector&);

INT Driver_11aeb0(ULevel* L, FVector& Location, const FVector& Extent, DWORD Flags)
{
    Escape((void*)&GZeroVector);
    Escape(&GMem);
    SingleLineCheckFn Fn = &ULevel::SingleLineCheck;
    Escape(&Fn);
    FCheckResult Hit(1.f);
    if (!L->SinglePointCheck(Hit, Location, Extent, Flags, L->GetLevelInfo()))
        return 1;
    if (Extent == GZeroVector)
        return 0;
    FVector Start = Location;
    INT bKeepTrying = 1;
    if (L->CheckSlice(Location, Extent, bKeepTrying))
        return 1;
    if (!bKeepTrying)
        return 0;
    Location = Start;
    return 0;
}
