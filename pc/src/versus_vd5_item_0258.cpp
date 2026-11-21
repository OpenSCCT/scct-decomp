// Work item w3 0258: RVA 0xf5250-0xf582c (LTCG-compiled object).
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned short TCHAR;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

class UClass;
class UnnamedClass_f5250;

class UObject
{
public:
    void *VTable;
    DWORD Fields04[8];
    UClass *Class;                // 0x24
};

// The class carries a prime (+0x10c) and the product of its ancestors'
// primes (+0x110), so a subclass test is one division.
class UClass : public UObject
{
public:
    UClass *SuperClass;           // 0x28
    char Pad2c[0x10c - 0x2c];
    DWORD ClassPrime;             // 0x10c
    DWORD ClassProduct;           // 0x110
};

inline UBOOL IsAFast(UObject *Obj, UClass *Base)
{
    if (Base) { if (Obj->Class != Base) return Obj->Class->ClassProduct % Base->ClassPrime == 0; return 1; } return 0;
}

// Retail 0x10c9241c..0x10c92438: eight class pointers the lists filter on.
extern UClass *GClass_f5250_A;
extern UClass *GClass_f5250_B;
extern UClass *GClass_f5250_C;
extern UClass *GClass_f5250_D;
extern UClass *GClass_f5250_E;
extern UClass *GClass_f5250_F;
extern UClass *GClass_f5250_G;
extern UClass *GClass_f5250_H;

// Untyped array storage (UE2 FArray); this module's Empty frees the block
// only when one is allocated.
class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    void Empty()
    {
        ArrayNum = 0;
        if (Data)
        {
            GMalloc->Free(Data);
            Data = 0;
            ArrayMax = 0;
        }
    }
};

template <class T> class TArray : public FArray
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    INT FindItemIndex(const T &Item) const
    {
        for (INT Index = 0; Index < ArrayNum; Index++)
            if (((T *)Data)[Index] == Item)
                return Index;
        return -1;
    }
};

// Retail 0x10a357f0 is the shared out-of-line FindItemIndex that the lists
// for classes C..H call (identical instantiations are folded at link time);
// this specialisation only declares it.
class AActor : public UObject {};
template <> class TArray<AActor *> : public FArray
{
public:
    AActor *&operator()(INT i) { return ((AActor **)Data)[i]; }
    INT FindItemIndex(AActor * const &Item) const;
};
// Defined here only so the linker can see it does not write the item; retail
// keeps it out of line.
#pragma auto_inline(off)
INT TArray<AActor *>::FindItemIndex(AActor * const &Item) const
{
    for (INT Index = 0; Index < ArrayNum; Index++)
        if (((AActor **)Data)[Index] == Item)
            return Index;
    return -1;
}
#pragma auto_inline(on)


// Owner of nine object lists at +0x5c..+0xe4 with a dirty mask at +0x138.
// The class is not identified; neutral name.
class UnnamedClass_f5250
{
public:
    char Pad00[0x5c];
    TArray<UObject *> ListA;      // 0x5c
    DWORD ListAExtra;
    TArray<UObject *> ListB;      // 0x6c
    DWORD ListBExtra;
    TArray<AActor *> ListC;      // 0x7c
    DWORD ListCExtra;
    TArray<AActor *> ListD;      // 0x8c
    DWORD ListDExtra;
    TArray<AActor *> ListE;      // 0x9c
    DWORD ListEExtra;
    TArray<AActor *> ListF;      // 0xac
    DWORD ListFExtra;
    TArray<AActor *> ListG;      // 0xbc
    DWORD ListGExtra;
    TArray<AActor *> ListH;      // 0xcc
    DWORD ListHExtra;
    TArray<UObject *> ListI;      // 0xdc
    DWORD ListIExtra;
    char PadEC[0x138 - 0xec];
    DWORD DirtyFlags;             // 0x138
    void EmptyLists();
    void RemoveObject(AActor *Obj);
    UBOOL IsKindC(UObject *Obj);
    UBOOL IsKindD(UObject *Obj);
    UBOOL IsKindE(UObject *Obj);
    UBOOL IsKindF(UObject *Obj);
    UBOOL IsKindG(UObject *Obj);
    UBOOL IsKindH(UObject *Obj);
};

// Retail 0xf8b90..0xf8cd0 (separate functions, item 0267), defined here only
// so the linker gives them their retail convention and keeps them out of line.
#pragma auto_inline(off)
UBOOL UnnamedClass_f5250::IsKindC(UObject *Obj) { return IsAFast(Obj, GClass_f5250_C); }
UBOOL UnnamedClass_f5250::IsKindD(UObject *Obj) { return IsAFast(Obj, GClass_f5250_D); }
UBOOL UnnamedClass_f5250::IsKindE(UObject *Obj) { return IsAFast(Obj, GClass_f5250_E); }
UBOOL UnnamedClass_f5250::IsKindF(UObject *Obj) { return IsAFast(Obj, GClass_f5250_F); }
UBOOL UnnamedClass_f5250::IsKindG(UObject *Obj) { return IsAFast(Obj, GClass_f5250_G); }
UBOOL UnnamedClass_f5250::IsKindH(UObject *Obj) { return IsAFast(Obj, GClass_f5250_H); }
#pragma auto_inline(on)

// ---------------------------------------------------------------------------
// RVA 0xf5250: clear Obj's slot in the list matching its class and mark that
// list dirty (this in ESI).
void UnnamedClass_f5250::RemoveObject(AActor *Obj)
{
    INT Index = ListI.FindItemIndex(Obj);
    if (Index != -1)
    {
        ListI(Index) = 0;
        DirtyFlags |= 0x800;
    }
    if (IsAFast(Obj, GClass_f5250_A))
    {
        Index = ListA.FindItemIndex(Obj);
        if (Index != -1) { ListA(Index) = 0; DirtyFlags |= 0x8; }
    }
    else if (IsAFast(Obj, GClass_f5250_B))
    {
        Index = ListB.FindItemIndex(Obj);
        if (Index != -1) { ListB(Index) = 0; DirtyFlags |= 0x10; }
    }
    else if (IsKindC(Obj))
    {
        Index = ListC.FindItemIndex(Obj);
        if (Index != -1) { ListC(Index) = 0; DirtyFlags |= 0x20; }
    }
    else if (IsKindD(Obj))
    {
        Index = ListD.FindItemIndex(Obj);
        if (Index != -1) { ListD(Index) = 0; DirtyFlags |= 0x40; }
    }
    else if (IsKindE(Obj))
    {
        Index = ListE.FindItemIndex(Obj);
        if (Index != -1) { ListE(Index) = 0; DirtyFlags |= 0x80; }
    }
    else if (IsKindF(Obj))
    {
        Index = ListF.FindItemIndex(Obj);
        if (Index != -1) { ListF(Index) = 0; DirtyFlags |= 0x100; }
    }
    else if (IsKindG(Obj))
    {
        Index = ListG.FindItemIndex(Obj);
        if (Index != -1) { ListG(Index) = 0; DirtyFlags |= 0x200; }
    }
    else if (IsKindH(Obj))
    {
        Index = ListH.FindItemIndex(Obj);
        if (Index != -1) { ListH(Index) = 0; DirtyFlags |= 0x400; }
    }
}

// ---------------------------------------------------------------------------
// RVA 0xf5500: empty every list and clear the dirty mask (this in ESI).
void UnnamedClass_f5250::EmptyLists()
{
    ListA.Empty();
    ListB.Empty();
    ListC.Empty();
    ListD.Empty();
    ListE.Empty();
    ListF.Empty();
    ListG.Empty();
    ListH.Empty();
    ListI.Empty();
    DirtyFlags = 0;
}

// ---------------------------------------------------------------------------
// ULevel (Engine). Only the members this module touches are laid out.
typedef unsigned char BYTE;
enum EName { NAME_None };
struct FName
{
    INT Index;
    FName(EName N) : Index(N) {}
};
class UFunction;

class UEventObject_f5660
{
public:
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = 0);  // slot 4
    UFunction *FindFunctionChecked(FName InName, INT Global = 0);                     // retail 0x16830
    void eventUnnamed_c84()
    {
        ProcessEvent(FindFunctionChecked((EName)0xc84), 0);
    }
};

// Level info: Actors(0) of a level (fields not identified).
class ALevelInfo_f5660
{
public:
    char Pad0[0x438];
    BYTE Setting438;                    // 0x438
    char Pad439[0x4dc - 0x439];
    UEventObject_f5660 *Listener4dc;    // 0x4dc
};

class AActor_f5660
{
public:
    void *VTable;
    DWORD Fields04[5];
    UObject *Outer;                     // 0x18
    DWORD ObjectFlags;                  // 0x1c
    DWORD Name;                         // 0x20
    UClass *Class;                      // 0x24
    char Pad28[0x1a4 - 0x28];
    class ULevel *XLevel;               // 0x1a4
    char Pad1a8[0x2df - 0x1a8];
    BYTE Flag2df;                       // 0x2df
    UBOOL IsA(UClass *SomeBase)
    {
        for (UClass *C = Class; C; C = C->SuperClass)
            if (C == SomeBase)
                return 1;
        return 0;
    }
};

// Retail 0x10cc52a8 is AActor's class (the iterator below sets XLevel on
// what it finds); 0x10cbd008 is an actor class not identified.
extern UClass AActor_StaticClass_f56d0;
extern UClass UnnamedActorClass_f56d0;

template <class T> inline T *Cast(AActor_f5660 *Src, UClass *TargetClass)
{
    return Src && Src->IsA(TargetClass) ? (T *)Src : 0;
}

// UE2 TObjectIterator<AActor> over UObject::GObjObjects (retail 0x10cc9e80).
extern TArray<AActor_f5660 *> GObjObjects_f56d0;
class FActorObjectIterator_f56d0
{
public:
    TArray<AActor_f5660 *> *Array;
    INT Index;
    FActorObjectIterator_f56d0();
    ~FActorObjectIterator_f56d0();
    void operator++()
    {
        while (++Index < Array->ArrayNum
            && (!(*Array)(Index) || !(*Array)(Index)->IsA(&AActor_StaticClass_f56d0)))
            ;
    }
    AActor_f5660 *operator->() { return (*Array)(Index); }
    operator UBOOL() { return Index < Array->ArrayNum; }
};

// Retail 0x1090c750 and 0x1094a550 (separate units): defined here only so
// the linker gives them their retail conventions and keeps them out of line.
#pragma auto_inline(off)
FActorObjectIterator_f56d0::FActorObjectIterator_f56d0()
: Array(&GObjObjects_f56d0), Index(-1)
{
    ++*this;
}
#pragma auto_inline(on)
// Retail calls this empty destructor out of line (0x1094a550, this pushed);
// the link here discards the call, which is why PostLoad does not match.
inline FActorObjectIterator_f56d0::~FActorObjectIterator_f56d0()
{
}

extern const TCHAR FArray_Add_Tag[];   // L"FArray::Add"
extern const TCHAR FArray_Tag[];       // L"FArray"

// Array of AActor pointers at ULevel +0x4a68; AddUniqueItem is retail
// 0x109c9bb0 (this in ESI, item in EBX).
class FUnnamedActorList_f56d0 : public TArray<AActor_f5660 *>
{
public:
    INT AddUniqueItem(AActor_f5660 * const &Item)
    {
        for (INT i = 0; i < ArrayNum; i++)
            if ((*this)(i) == Item)
                return i;
        INT Index = ArrayNum;
        if (++ArrayNum > ArrayMax)
        {
            ArrayMax = ArrayNum + 3 * ArrayNum / 8 + 32;
            if (Data)
                Data = GMalloc->Realloc(Data, ArrayMax * sizeof(AActor_f5660 *), FArray_Tag);
            else
            {
                Data = GMalloc->Malloc(ArrayMax * sizeof(AActor_f5660 *), FArray_Add_Tag);
                (*this)(Index) = Item;
                return Index;
            }
        }
        (*this)(Index) = Item;
        return Index;
    }
};

// Retail 0x10a090c0 (large; this in EAX) and 0x109f8950 (this pushed): the
// level's model rebuild and a random table initialiser. Only declared shapes
// are needed; the bodies here are stand-ins that keep them out of line.
class UUnnamedModel_f56d0
{
public:
    INT Field58;
    void Rebuild();
};
struct FUnnamedNoise_f56d0
{
    float Values[16];
    void Init();
};
void UnnamedRebuildHelper_f56d0(UUnnamedModel_f56d0 *M);
float UnnamedRand_f56d0();
#pragma auto_inline(off)
void UUnnamedModel_f56d0::Rebuild()
{
    UnnamedRebuildHelper_f56d0(this);
}
void FUnnamedNoise_f56d0::Init()
{
    for (INT i = 0; i < 4; i++)
        for (INT j = 0; j < 4; j++)
            Values[i * 4 + j] = UnnamedRand_f56d0() * Values[j];
}
#pragma auto_inline(on)

// Global object read during PostLoad (retail 0x10c946cc); type not recovered.
struct FUnnamedSettings_90b00
{
    char Pad0[0x80];
    INT Field80;                    // 0x80
};
extern FUnnamedSettings_90b00 *GUnnamedSettings_90b00;

// Retail 0x10a12e60 and 0x10ca7068: a global object and the call this
// module makes on it first (neither identified; callee pops its argument).
struct FUnnamedGlobal_f5660 { INT Pad; };
extern FUnnamedGlobal_f5660 GUnnamedGlobal_f5660;
void __stdcall UnnamedFunc_a12e60(FUnnamedGlobal_f5660 *G);

class ULevel
{
public:
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual void Slot5();
    virtual void Slot6();
    virtual void Slot7();
    virtual void PostLoad();            // slot 8
    DWORD Fields04[5];
    UObject *Outer;                     // 0x18
    DWORD ObjectFlags;                  // 0x1c
    char Pad20[0x2c - 0x20];
    AActor_f5660 **ActorData;           // 0x2c  Actors
    INT ActorNum;                       // 0x30
    INT ActorMax;                       // 0x34
    char Pad38[0x13c - 0x38];
    UUnnamedModel_f56d0 *Model;         // 0x13c
    char Pad140[0x1ac - 0x140];
    FUnnamedNoise_f56d0 Noise;          // 0x1ac
    char Pad1ec[0x39e8 - 0x1ec];
    void *LevelInfoField480;            // 0x39e8
    char Pad39ec[0x4a68 - 0x39ec];
    FUnnamedActorList_f56d0 ActorList;  // 0x4a68
    void SetLevelSetting(BYTE NewValue);
    ALevelInfo_f5660 *GetLevelInfo() { return (ALevelInfo_f5660 *)ActorData[0]; }
    void LoadPerObjectData();           // retail 0x10916f70 (UObject, this in ESI)
};

#pragma auto_inline(off)
void ULevel::LoadPerObjectData()
{
    if (ObjectFlags & 0x20)
    {
        UnnamedRebuildHelper_f56d0((UUnnamedModel_f56d0 *)Outer);
        UnnamedRebuildHelper_f56d0((UUnnamedModel_f56d0 *)this);
    }
}
#pragma auto_inline(on)

// ---------------------------------------------------------------------------
// RVA 0xf56d0: ULevel::PostLoad (vtable slot 8). Near miss: see the
// iterator destructor note; the helper stand-ins also give 0x109f8950 a
// register argument where retail pushes it.
void ULevel::PostLoad()
{
    // UObject::PostLoad, inlined.
    ObjectFlags |= 0x20000000;
    if (ObjectFlags & 0x100)
        LoadPerObjectData();

    for (FActorObjectIterator_f56d0 It; It; ++It)
        if (It->Outer == Outer)
            It->XLevel = this;

    INT NetMode = GUnnamedSettings_90b00->Field80;
    if (NetMode != 1 && NetMode != 2 && NetMode != 3)
        Model->Rebuild();
    Noise.Init();

    ActorList.Empty();
    for (INT i = 0; i < ActorNum; i++)
    {
        AActor_f5660 *Actor = ActorData[i];
        if (Actor && Actor->IsA(&UnnamedActorClass_f56d0))
            ActorList.AddUniqueItem(Cast<AActor_f5660>(Actor, &UnnamedActorClass_f56d0));
    }
    LevelInfoField480 = (char *)ActorData[0] + 0x480;
}

// RVA 0xf5660 (this in ESI). Name event 0xc84 is not recovered.
void ULevel::SetLevelSetting(BYTE NewValue)
{
    UnnamedFunc_a12e60(&GUnnamedGlobal_f5660);
    GetLevelInfo()->Setting438 = NewValue;
    if (GetLevelInfo()->Listener4dc)
        GetLevelInfo()->Listener4dc->eventUnnamed_c84();
    for (INT i = 0; i < ActorNum; i++)
        if (ActorData[i])
            ActorData[i]->Flag2df = 0;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_f5500(UnnamedClass_f5250 *A)
{
    Escape(&GMalloc);
    A->EmptyLists();
}
void Driver_f5250(UnnamedClass_f5250 *A, AActor *Obj)
{
    Escape(&GClass_f5250_A);
    Escape(&GClass_f5250_B);
    A->RemoveObject(Obj);
}

void Driver_f5660(ULevel *Level, BYTE B)
{
    Level->SetLevelSetting(B);
}
inline void *operator new(unsigned int, void *Mem) { return Mem; }
void Driver_f56d0(ULevel *Level, void *Mem)
{
    new (Mem) ULevel;
    Escape(&GUnnamedSettings_90b00);
    Level->PostLoad();
}
