// Work item 0305 (w3): Versus RVA 0x1060f0-0x10647c, Engine.
// This stretch was built with /GL and linked with /LTCG: the rain-object
// constructor (0x106140) takes `this` in EDI and its owner on the stack, the
// TArray<FRainDrop> serializer (0x1061b0) takes the archive in EAX and the
// array in EBX, the element serializer (0x106260) takes the element in EAX and
// the archive in ESI, and ULevel::DestroyActor (0x11a790) takes `this` on the
// stack (written here as a __stdcall member).
// Class names other than AERainVolume (reflected vtable 0x303c40) are neutral.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef float FLOAT;
typedef unsigned __int64 QWORD;

#pragma pack(push, 4)

class UObject;
class UClass;
class FOutputDevice;
class AActor;
class ULevel;

inline void *operator new(unsigned int, void *Mem) { return Mem; }

struct FCompactIndex
{
    INT Value;
};
#define AR_INDEX(intref) (*(FCompactIndex *)&(intref))

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);            // +0x04
    virtual void SerializeBits(void *V, INT LengthBits);    // +0x08
    virtual void SerializeInt(DWORD &Value, DWORD Max);     // +0x0c
    virtual void Preload(UObject *Object);                  // +0x10
    virtual void CountBytes(DWORD InNum, DWORD InMax);      // +0x14

    UBOOL IsLoading() { return ArIsLoading; }
    UBOOL IsSaving() { return ArIsSaving; }

    friend FArchive &operator<<(FArchive &Ar, BYTE &B)
    {
        Ar.Serialize(&B, 1);
        return Ar;
    }
    friend FArchive &operator<<(FArchive &Ar, INT &I)
    {
        Ar.Serialize(&I, 4);
        return Ar;
    }
    friend FArchive &operator<<(FArchive &Ar, FLOAT &F)
    {
        Ar.Serialize(&F, 4);
        return Ar;
    }
    friend FArchive &operator<<(FArchive &Ar, FCompactIndex &I);

    INT ArVer;
    INT ArNetVer;
    INT ArLicenseeVer;
    UBOOL ArIsLoading;
    UBOOL ArIsSaving;
    UBOOL ArIsTrans;
};

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    INT Add(INT Count, INT ElementSize);        // 0x44e0
    void Empty(INT ElementSize, INT Slack);     // 0x4550
};

template <class T> class TArray : public FArray
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    void CountBytes(FArchive &Ar) { Ar.CountBytes(ArrayNum * sizeof(T), ArrayMax * sizeof(T)); }
    void Empty(INT Slack) { FArray::Empty(sizeof(T), Slack); }

    friend FArchive &operator<<(FArchive &Ar, TArray &A)
    {
        A.CountBytes(Ar);
        if (Ar.IsLoading()) {
            INT NewNum;
            Ar << AR_INDEX(NewNum);
            A.Empty(NewNum);
            for (INT i = 0; i < NewNum; i++)
                Ar << *new(&((T *)A.Data)[A.Add(1, sizeof(T))]) T;
        } else {
            Ar << AR_INDEX(A.ArrayNum);
            for (INT i = 0; i < A.ArrayNum; i++)
                Ar << A(i);
        }
        return Ar;
    }
};

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector &operator=(const FVector &V) { X = V.X; Y = V.Y; Z = V.Z; return *this; }
    friend FArchive &operator<<(FArchive &Ar, FVector &V)
    {
        return Ar << V.X << V.Y << V.Z;
    }
};

struct FColor
{
    BYTE B, G, R, A;
    friend FArchive &operator<<(FArchive &Ar, FColor &C)
    {
        return Ar << C.R << C.G << C.B << C.A;
    }
};

// 24-byte element of the rain object's array (neutral name).
struct FRainDrop
{
    FVector Location;
    FColor Color;
    FLOAT Param0;
    FLOAT Param1;
};

class FExec
{
public:
    virtual UBOOL Exec(const TCHAR *Cmd, FOutputDevice &Ar);
};

enum EName { NAME_None = 0 };
struct FName
{
    INT Index;
    FName(EName N) : Index(N) {}
};
extern FOutputDevice *GError;

class UObject
{
public:
    UObject() {}
    virtual ~UObject();
    virtual void V01(); virtual void V02(); virtual void V03(); virtual void V04();
    virtual void V05(); virtual void V06(); virtual void V07(); virtual void V08();
    virtual void Destroy();                                                  // +0x24, 0x15ce0
    virtual void V10(); virtual void V11(); virtual void V12(); virtual void V13();
    virtual void V14(); virtual void V15(); virtual void V16(); virtual void V17();
    virtual UBOOL ScriptConsoleExec(const TCHAR *Cmd, FOutputDevice &Ar, UObject *Executor); // +0x48

    INT Index;
    UObject *HashNext;
    void *StateFrame;
    UObject *_Linker;
    INT _LinkerIndex;
    UObject *Outer;
    DWORD ObjectFlags;
    INT Name;
    UClass *Class;

    static UObject *StaticAllocateObject(UClass *Class, UObject *InOuter = 0, FName InName = FName(NAME_None),
                                         DWORD SetFlags = 0, UObject *Template = 0, FOutputDevice *Error = GError,
                                         UObject *Ptr = 0, UObject *SubobjectRoot = 0);
};

extern FOutputDevice *GError;

class USubsystem : public UObject, public FExec
{
};
class UEngine : public USubsystem
{
};
extern USubsystem *GSys;

class ULevel : public UObject
{
public:
    BYTE Pad28[0xf0 - 0x28];
    UEngine *Engine;                    // +0xf0
    UBOOL Exec(const TCHAR *Cmd, FOutputDevice &Ar);                    // 0xf6450
    UBOOL __stdcall DestroyActor(AActor *Actor, UBOOL bNetForce);        // 0x11a790
};

class AActor : public UObject
{
public:
    BYTE Pad28[0x1a0 - 0x28];
    class ALevelInfo *Level;            // +0x1a0
    ULevel *XLevel;                     // +0x1a4
    ULevel *GetLevel() const { return XLevel; }
};

class ALevelInfo : public AActor
{
public:
    BYTE Pad1a8[0x4dc - 0x1a8];
    UObject *Game;                      // +0x4dc
};

class APlayerController : public AActor
{
public:
    BYTE Pad1a8[0x2fc - 0x1a8];
    UObject *Pawn;                      // +0x2fc
    BYTE Pad300[0x52c - 0x300];
    UObject *ExecTarget52c;             // +0x52c
    BYTE Pad530[0x5b0 - 0x530];
    UObject *ExecTarget5b0;             // +0x5b0
    BYTE Pad5b4[0x5b8 - 0x5b4];
    UObject *ExecTarget5b8;             // +0x5b8
};

// Render-resource style members built by the rain object (0xa2f40, 0x1126e0):
// a TArray, a cache id from the global counter and a revision.
extern QWORD GCacheIDCounter;
inline QWORD MakeCacheID(INT Base) { return GCacheIDCounter++ * 256 + Base; }

class FRainStreamA
{
public:
    virtual void V00();
    TArray<FRainDrop> Items;
    QWORD CacheId;
    INT Revision;
    FRainStreamA();
};
class FRainStreamB
{
public:
    virtual void V00();
    TArray<FRainDrop> Items;
    QWORD CacheId;
    INT Revision;
    FRainStreamB();
};
// RVA 0xa2f40 and 0x1126e0 (defined so the link gives them their ESI
// convention; retail does not inline them).
__declspec(noinline) FRainStreamA::FRainStreamA() { CacheId = MakeCacheID(0xe1); Revision = 0; }
__declspec(noinline) FRainStreamB::FRainStreamB() { CacheId = MakeCacheID(0xe2); Revision = 0; }

extern FVector *GRainVecA;
extern FVector *GRainVecB;

class AERainVolume;

// Base of the rain object (vtable 0x10c0bae8, neutral name).
class URainBase : public UObject
{
public:
    FVector VecA;                       // +0x28
    FVector VecB;                       // +0x34
    INT Field40;
    TArray<INT> Items44;
    URainBase() : VecA(*GRainVecA), VecB(*GRainVecB), Field40(0) {}
};

// Rain object (vtable 0x10c0b368, neutral name).
class URainObject : public URainBase
{
public:
    AERainVolume *Volume;               // +0x50
    FRainStreamA StreamA;               // +0x54
    FRainStreamB StreamB;               // +0x70
    URainObject(AERainVolume *InVolume);
    static UClass PrivateStaticClass;
    static UClass *StaticClass() { return &PrivateStaticClass; }
    void *operator new(unsigned int, UObject *InOuter, FName InName = FName(NAME_None), DWORD SetFlags = 0)
    {
        return StaticAllocateObject(StaticClass(), InOuter, InName, SetFlags);
    }
};

class AERainVolume : public AActor
{
public:
    BYTE Pad1a8[0x324 - 0x1a8];
    URainObject *Rain;                  // +0x324
    void CreateRain();                  // vtable 0x303c40 slot 44
};

// RVA 0x1060f0.
void AERainVolume::CreateRain()
{
    if (Rain == 0)
        Rain = new(this, NAME_None) URainObject(this);
}

// RVA 0x106140.
URainObject::URainObject(AERainVolume *InVolume)
    : Volume(InVolume)
{
}

// RVA 0x1ea40 (published elsewhere; defined here so the link gives it its
// register convention).
FArchive &operator<<(FArchive &Ar, FCompactIndex &I)
{
    if (!Ar.IsLoading() && !Ar.IsSaving()) {
        Ar.Serialize(&I.Value, 4);
    } else {
        INT Original = I.Value;
        DWORD V = Original >= 0 ? Original : -Original;
        BYTE B0 = ((I.Value >= 0) ? 0 : 0x80) + ((V < 0x40) ? V : ((V & 0x3f) + 0x40));
        I.Value = 0;
        Ar << B0;
        if (B0 & 0x40) {
            V >>= 6;
            BYTE B1 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
            Ar << B1;
            if (B1 & 0x80) {
                V >>= 7;
                BYTE B2 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
                Ar << B2;
                if (B2 & 0x80) {
                    V >>= 7;
                    BYTE B3 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
                    Ar << B3;
                    if (B3 & 0x80) {
                        V >>= 7;
                        BYTE B4 = V;
                        Ar << B4;
                        I.Value = B4;
                    }
                    I.Value = (I.Value << 7) + (B3 & 0x7f);
                }
                I.Value = (I.Value << 7) + (B2 & 0x7f);
            }
            I.Value = (I.Value << 7) + (B1 & 0x7f);
        }
        I.Value = (I.Value << 6) + (B0 & 0x3f);
        if (B0 & 0x80)
            I.Value = -I.Value;
    }
    return Ar;
}

// RVA 0x106260: FArchive& operator<<(FArchive&, FRainDrop&).
FArchive &operator<<(FArchive &Ar, FRainDrop &D)
{
    return Ar << D.Location << D.Color << D.Param0 << D.Param1;
}

// RVA 0x1061b0 is TArray<FRainDrop>'s operator<< (template above).
FArchive &SerializeRainDrops(FArchive &Ar, TArray<FRainDrop> &A)
{
    return Ar << A;
}

// Object that owns a spawned actor at +0x30 (neutral name).
class UActorHolder : public UObject
{
public:
    INT Field28;
    INT Field2c;
    AActor *SpawnedActor;               // +0x30
    void Destroy();
};
extern UBOOL GActorHolderEnabled;       // 0x10c9690c

struct AActorWithField4a4 : public AActor
{
    BYTE Pad1a8[0x4a4 - 0x1a8];
    INT Field4a4;
};

// RVA 0x1062e0.
void UActorHolder::Destroy()
{
    if (GActorHolderEnabled && SpawnedActor) {
        ULevel *Level = SpawnedActor->GetLevel();
        ((AActorWithField4a4 *)SpawnedActor)->Field4a4 = 0;
        Level->DestroyActor(SpawnedActor, 1);
        SpawnedActor = 0;
    }
    UObject::Destroy();
}

// Player-side exec handler; `this` is the FExec subobject at +0x28.
class UPlayerBase : public UObject
{
};
class UExecPlayer : public UPlayerBase, public FExec
{
public:
    APlayerController *Actor;           // +0x2c (FExec+4)
    BYTE Pad30[0x50 - 0x30];
    UActorHolder *Holder;               // +0x50 (FExec+0x28)
    UBOOL Exec(const TCHAR *Cmd, FOutputDevice &Ar);
};

// RVA 0x106320.
UBOOL UExecPlayer::Exec(const TCHAR *Cmd, FOutputDevice &Ar)
{
    if (!Actor)
        return 0;
    if (Actor->GetLevel()->Exec(Cmd, Ar))
        return 1;
    if (Actor->Level && Actor->Level->Game && Actor->Level->Game->ScriptConsoleExec(Cmd, Ar, Actor->Pawn))
        return 1;
    if (Actor->ExecTarget52c && Actor->ExecTarget52c->ScriptConsoleExec(Cmd, Ar, Actor->Pawn))
        return 1;
    if (Actor->ExecTarget5b0 && Actor->ExecTarget5b0->ScriptConsoleExec(Cmd, Ar, Actor->Pawn))
        return 1;
    if (Actor->ScriptConsoleExec(Cmd, Ar, Actor->Pawn))
        return 1;
    if (Actor->ExecTarget5b8 && Actor->ExecTarget5b8->ScriptConsoleExec(Cmd, Ar, Actor->Pawn))
        return 1;
    if (Actor->Pawn && Actor->Pawn->ScriptConsoleExec(Cmd, Ar, Actor->Pawn))
        return 1;
    if (Actor->XLevel->Engine->Exec(Cmd, Ar))
        return 1;
    if (GSys && GSys->Exec(Cmd, Ar))
        return 1;
    if (Holder->SpawnedActor && Holder->SpawnedActor->ScriptConsoleExec(Cmd, Ar, Actor->Pawn))
        return 1;
    return 0;
}

#pragma pack(pop)

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_1060f0(AERainVolume *V)
{
    Escape(&GError); Escape(&GRainVecA); Escape(&GRainVecB); Escape(&GCacheIDCounter);
    void (AERainVolume::*F)() = &AERainVolume::CreateRain;
    Escape(&F);
    (V->*F)();
}
void Driver_1061b0(FArchive *Ar, TArray<FRainDrop> *A)
{
    SerializeRainDrops(*Ar, *A);
}
void Driver_1062e0(void *Mem)
{
    Escape(&GActorHolderEnabled);
    Escape(new(Mem) UActorHolder);
}
void Driver_106320(void *Mem)
{
    Escape(&GSys);
    Escape(new(Mem) UExecPlayer);
}
