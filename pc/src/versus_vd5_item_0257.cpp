// Work item 0257 (wave 3): Versus RVA 0xf4e30-0xf5242, Engine UnLevel.cpp
// (ULevelBase), all from the LTCG link.
// 0xf4e30 ULevelBase::ULevelBase(UEngine*): twelve TTransArray<AActor*> owned
//         by the level, Engine, default FURL (this on the stack).
// 0xf4f80 ULevelBase::Serialize: the old-version actor list serializer from
//         Unreal Engine 2 UnLevel.cpp, then the URL and the NetDriver.
// 0xf5050 ULevelBase::Destroy: deletes the NetDriver.
// 0xf5080 / 0xf50f0: Versus additions that sort an actor into the level's
//         extra actor lists. Names not recovered (neutral names used); the
//         eleven extra lists are named after their offsets.
// Built with try_ltcg.py --flags "/O2 /Gy /GX", roots Driver_f4e30 and
// Driver_f50f0. 0xf4e30, 0xf4f80, 0xf5050 and 0xf5080 match. 0xf50f0 is near:
// retail materialises each class test as 0/1 (neg/sbb/inc, test) before the
// branch; here the remainder is tested directly (5 bytes shorter per test).
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;

class FArchive;
class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;                 // 0x10c73bf0

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    FArray() { ArrayNum = 0; ArrayMax = 0; Data = 0; }
    ~FArray()
    {
        if (Data)
            GMalloc->Free(Data);
    }
    void Remove(INT Index, INT Count, INT ElementSize);     // RVA 0x119c0
    INT Add(INT Count, INT ElementSize);                    // RVA 0x44e0
    void Empty(INT ElementSize, INT Slack);                 // RVA 0x4550
};
template<class T> class TArray : public FArray
{
public:
    ~TArray() { Remove(0, ArrayNum); }
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    void Remove(INT Index, INT Count = 1) { FArray::Remove(Index, Count, sizeof(T)); }
    void Empty(INT Slack = 0) { FArray::Empty(sizeof(T), Slack); }
    INT Add(INT Count = 1) { return FArray::Add(Count, sizeof(T)); }
    void CountBytes(FArchive &Ar);
    __declspec(noinline) INT AddItem(const T &Item)         // RVA 0x1efa0
    {
        INT Index = FArray::Add(1, sizeof(T));
        (*this)(Index) = Item;
        return Index;
    }
};

class UObject;
class FArchive;
template<class T> class TTransArray : public TArray<T>
{
public:
    TTransArray(UObject *InOwner) : Owner(InOwner) {}
    UObject *Owner;
};

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);            // +0x04
    virtual void Slot08(); virtual void Slot0c(); virtual void Slot10();
    virtual void CountBytes(DWORD InNum, DWORD InMax);      // +0x14
    virtual FArchive &operator<<(UObject *&Res);            // +0x18
    INT ArVer, ArNetVer, ArLicenseeVer, ArIsLoading, ArIsSaving, ArIsTrans;
    UBOOL IsLoading() const { return ArIsLoading; }
    UBOOL IsSaving() const { return ArIsSaving; }
    UBOOL IsTrans() const { return ArIsTrans; }
    FArchive &operator<<(INT &V) { Serialize(&V, sizeof(V)); return *this; }
};

template<class T> inline void TArray<T>::CountBytes(FArchive &Ar)
{
    Ar.CountBytes(ArrayNum * sizeof(T), ArrayMax * sizeof(T));
}

struct FName { INT Index; };
class UClass;

class UObject
{
public:
    virtual void Slot00(); virtual void Slot04(); virtual void Slot08();
    virtual ~UObject();                                     // +0x0c
    virtual void Destroy();
    virtual void Serialize(FArchive &Ar);
    INT Index;
    UObject *HashNext;
    void *StateFrame;
    void *_Linker;
    INT _LinkerIndex;
    UObject *Outer;
    DWORD ObjectFlags;
    FName Name;
    UClass *Class;                                          // +0x24
    UBOOL IsA(UClass *Other) const;
};

// Versus class records carry a key; a class is a subclass of another when
// its multiple is divisible by the other's key.
class UClass : public UObject
{
public:
    DWORD Pad[(0x10c - 0x28) / 4];
    DWORD ClassKey;                                         // +0x10c
    DWORD ClassMultiple;                                    // +0x110
    UBOOL IsChildOf(const UClass *Other) const;
};
UBOOL UClass::IsChildOf(const UClass *Other) const
{
    return ClassMultiple % Other->ClassKey == 0;
}
UBOOL UObject::IsA(UClass *Other) const
{
    return Class == Other || Class->IsChildOf(Other);
}

class ULevelBase;
class AActor : public UObject
{
public:
    BYTE Pad[0x2d1 - 0x28];
    BYTE b2d1;                                              // +0x2d1
    BYTE Physics;                                           // +0x2d2
    BYTE Pad2[0x2dd - 0x2d3];
    BYTE b2dd;                                              // +0x2dd
    BYTE Pad3[0x2e8 - 0x2de];
    DWORD Bits2e8_0 : 11;
    DWORD bFlag2e8_11 : 1;                                  // 0x800
    DWORD Bits2e8_12 : 5;
    DWORD bFlag2e8_17 : 1;                                  // 0x20000
    DWORD Bits2e8_18 : 14;
    DWORD Bits2ec_0 : 3;
    DWORD bFlag2ec_3 : 1;                                   // 0x8

    // Tests used by the level's list sorting (RVAs 0xf8b90-0xf8d50).
    UBOOL Test_f8d50(ULevelBase *Level);
    UBOOL Test_f8d10(ULevelBase *Level);
    UBOOL Test_f8cd0(ULevelBase *Level);
    UBOOL Test_f8c90(ULevelBase *Level);
    UBOOL Test_f8c50(ULevelBase *Level);
    UBOOL Test_f8c10(ULevelBase *Level);
    UBOOL Test_f8bd0(ULevelBase *Level);
    UBOOL Test_f8b90(ULevelBase *Level);
};

class UNetDriver : public UObject {};
class UEngine;

// Stand-in for FString (Data, ArrayNum, ArrayMax).
class FString : public FArray
{
public:
    FString();
    ~FString();
};
class FURL
{
public:
    FString Protocol;
    FString Host;
    INT Port;
    FString Map;
    DWORD Pad[3];
    FString Portal;
    FURL();                                                 // RVA 0xca9b0
};
FArchive &operator<<(FArchive &Ar, FURL &U);                // RVA 0x133420

class FNetworkNotify
{
public:
    virtual INT NotifyAcceptingConnection() = 0;
};

extern UClass *GActorListClassA;                            // 0x10c9241c
extern UClass *GActorListClassB;                            // 0x10c92420

class ULevelBase : public UObject, public FNetworkNotify
{
public:
    TTransArray<AActor *> Actors;                           // +0x2c
    TTransArray<AActor *> List3c, List4c, List5c, List6c, List7c, List8c;
    TTransArray<AActor *> List9c, ListAc, ListBc, ListCc, ListDc;
    UNetDriver *NetDriver;                                  // +0xec
    UEngine *Engine;                                        // +0xf0
    FURL URL;                                               // +0xf4

    ULevelBase(UEngine *InEngine);
    void Destroy();
    void Serialize(FArchive &Ar);
    INT NotifyAcceptingConnection();
    void SortActor_f50f0(AActor *Actor);
    UBOOL ActorTest_f5080(AActor *Actor);
};


// RVA 0xf4e30
ULevelBase::ULevelBase(UEngine *InEngine)
    : Actors(this), List3c(this), List4c(this), List5c(this), List6c(this), List7c(this),
      List8c(this), List9c(this), ListAc(this), ListBc(this), ListCc(this), ListDc(this),
      Engine(InEngine)
{
}

// RVA 0xf4f80
void ULevelBase::Serialize(FArchive &Ar)
{
    UObject::Serialize(Ar);
    if (!Ar.IsTrans()) {
        INT DbNum = Actors.Num(), DbMax = DbNum;
        Actors.CountBytes(Ar);
        Ar << DbNum << DbMax;
        if (Ar.IsLoading()) {
            Actors.Empty(DbNum);
            Actors.Add(DbNum);
        }
        for (INT i = 0; i < Actors.Num(); i++)
            Ar << (UObject *&)Actors(i);
    }
    Ar << URL;
    if (!Ar.IsLoading() && !Ar.IsSaving())
        Ar << (UObject *&)NetDriver;
}

// RVA 0xf5050
void ULevelBase::Destroy()
{
    if (NetDriver) {
        delete NetDriver;
        NetDriver = 0;
    }
    UObject::Destroy();
}

// RVA 0xf5080
UBOOL ULevelBase::ActorTest_f5080(AActor *Actor)
{
    ULevelBase *Level = this;
    if (!Actor)
        return 0;
    if (Actor == Level->Actors(0) || Actor->Test_f8d50(Level) || Actor->Test_f8d10(Level))
        return 1;
    if (!Actor->b2dd)
        return 0;
    if (!Actor->bFlag2e8_11)
        return 1;
    if (Actor->b2d1 && (Actor->bFlag2e8_17 || Actor->Physics == 0x16))
        return 1;
    return Actor->bFlag2ec_3;
}

// RVA 0xf50f0
void ULevelBase::SortActor_f50f0(AActor *Actor)
{
    if (ActorTest_f5080(Actor))
        ListDc(ListDc.Add()) = Actor;
    if (GActorListClassA && Actor->IsA(GActorListClassA)) {
        List5c(List5c.Add()) = Actor;
        return;
    }
    if (GActorListClassB && Actor->IsA(GActorListClassB)) {
        List6c(List6c.Add()) = Actor;
        return;
    }
    if (Actor->Test_f8cd0(this))
        List7c(List7c.Add()) = Actor;
    else if (Actor->Test_f8c90(this))
        List8c(List8c.Add()) = Actor;
    else if (Actor->Test_f8c50(this))
        List9c.AddItem(Actor);
    else if (Actor->Test_f8c10(this))
        ListAc.AddItem(Actor);
    else if (Actor->Test_f8bd0(this))
        ListBc.AddItem(Actor);
    else if (Actor->Test_f8b90(this))
        ListCc.AddItem(Actor);
}

// Scaffolding for the link, not part of the unit. Callees that retail
// reaches through whole-program conventions are given stand-in bodies so the
// link gives them those conventions; their own code is matched elsewhere.
void Escape(void *);
void Opaque(void *, void *);
__declspec(noinline) FURL::FURL() { Escape(this); }
__declspec(noinline) FArchive &operator<<(FArchive &Ar, FURL &U) { Escape(&U); Escape(&U.Host); Escape(&U.Port); return Ar; }
#define STANDIN(n) __declspec(noinline) UBOOL AActor::Test_##n(ULevelBase *Level) { Escape(this); Escape(&Outer); Escape(&ObjectFlags); return Level == (ULevelBase *)0x##n; }
STANDIN(f8d50) STANDIN(f8d10) STANDIN(f8cd0) STANDIN(f8c90)
STANDIN(f8c50) STANDIN(f8c10) STANDIN(f8bd0) STANDIN(f8b90)
inline void *operator new(unsigned int, void *Mem) { return Mem; }
void Driver_f4e30(void *Mem, UEngine *E) { new (Mem) ULevelBase(E); }
void Driver_f50f0(ULevelBase *L, AActor *A)
{
    Escape(&GActorListClassA); Escape(&GActorListClassB);
    L->SortActor_f50f0(A);
}
