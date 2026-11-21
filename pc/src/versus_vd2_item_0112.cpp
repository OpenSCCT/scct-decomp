// Work item 0112: Versus RVA 0x1d6f0-0x1d98f, Core UnObj.cpp (LTCG objects).
// 0x1d6f0 UObject::StaticConstructObject: StaticAllocateObject then the
//         class's ClassConstructor (UClass+0x104).
// 0x1d730 UObject::SerializeRootSet: Ar << GObjRoot, then every object whose
//         flags pass KeepFlags/RequiredFlags.
// 0x1d7c0 compacts GObjObjects (renumbering UObject::Index), shrinks it and
//         empties GObjAvailable. Name not recovered: CompactObjects_1d7c0.
// 0x1d8d0 FArchiveTagUsed::FArchiveTagUsed (vtable 0x10c0cff8): resets
//         GGarbageRefCount and tags every object RF_Unreachable|RF_TagGarbage
//         and every name RF_Unreachable, as in Unreal Engine 2's UnObj.cpp.
// GObjObjects/GObjAvailable are the TArrays at 0x10cc9e80/0x10cc9e8c,
// GObjRoot 0x10cc9ea4, FName::Names 0x10cc9e5c, GGarbageRefCount 0x10c925fc.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

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
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FArray()
    {
        if (Data)
            GMalloc->Free(Data);
    }
    void Remove(INT Index, INT Count, INT ElementSize);     // RVA 0x119c0
    INT Add(INT Count, INT ElementSize);                    // RVA 0x44e0
    void Empty(INT ElementSize, INT Slack);                 // RVA 0x4550
    void Shrink(INT ElementSize)
    {
        if (ArrayMax != ArrayNum) {
            ArrayMax = ArrayNum;
            Data = GMalloc->Realloc(Data, ArrayMax * ElementSize, L"FArray");
        }
    }
    void Empty()
    {
        ArrayNum = 0;
        if (Data) {
            GMalloc->Free(Data);
            Data = 0;
            ArrayMax = 0;
        }
    }
};
template<class T> class TArray : public FArray
{
public:
    ~TArray() { Remove(0, ArrayNum); }
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    void Remove(INT Index, INT Count = 1) { FArray::Remove(Index, Count, sizeof(T)); }
    void Shrink() { FArray::Shrink(sizeof(T)); }
};

class FOutputDevice;
class UObject;
class UClass;

struct FName
{
    INT Index;
};
struct FNameEntry
{
    INT Index;
    DWORD Flags;
};
extern TArray<FNameEntry *> FName_Names;   // FName::Names, 0x10cc9e5c

enum EObjectFlags
{
    RF_Unreachable = 0x00000002,
    RF_TagGarbage = 0x00000040,
};

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);            // +0x04
    virtual void Slot08(); virtual void Slot0c(); virtual void Slot10();
    virtual void CountBytes(DWORD InNum, DWORD InMax);      // +0x14
    virtual FArchive &operator<<(UObject *&Res);            // +0x18
    FArchive()
        : ArVer(0xaf), ArNetVer(2000), ArLicenseeVer(0), ArIsLoading(0), ArIsSaving(0),
          ArIsTrans(0), ArIsPersistent(0), ArForEdit(1), ArForClient(1), ArForServer(1),
          ArIsError(0), ArIsCriticalError(0), ArContainsCode(3), ArFlags3(0), ArMaxSerializeSize(-1)
    {}
    INT ArVer, ArNetVer, ArLicenseeVer, ArIsLoading, ArIsSaving, ArIsTrans, ArIsPersistent;
    INT ArForEdit, ArForClient, ArForServer, ArIsError, ArIsCriticalError, ArContainsCode;
    INT ArFlags3, ArMaxSerializeSize;
};

FArchive &operator<<(FArchive &Ar, TArray<UObject *> &A);   // RVA 0xf85a0

class UObject
{
public:
    virtual ~UObject();
    INT Index;
    UObject *HashNext;
    void *StateFrame;
    void *_Linker;
    INT _LinkerIndex;
    UObject *Outer;
    DWORD ObjectFlags;
    FName Name;
    UClass *Class;

    void SetFlags(DWORD NewFlags) { ObjectFlags |= NewFlags; }
    DWORD GetFlags() const { return ObjectFlags; }

    static UObject *StaticAllocateObject(UClass *Class, UObject *InOuter, FName Name, DWORD SetFlags,
                                         UObject *Template, FOutputDevice *Error, UObject *Ptr,
                                         UObject *SubobjectRoot);
    static UObject *StaticConstructObject(UClass *Class, UObject *InOuter, FName Name, DWORD SetFlags,
                                          UObject *Template, FOutputDevice *Error, UObject *SubobjectRoot);
    static void SerializeRootSet(FArchive &Ar, DWORD KeepFlags, DWORD RequiredFlags);

    static TArray<UObject *> GObjObjects;   // 0x10cc9e80
    static TArray<INT> GObjAvailable;       // 0x10cc9e8c
    static TArray<UObject *> GObjRoot;      // 0x10cc9ea4
};

class UClass : public UObject
{
public:
    DWORD Pad[(0x104 - 0x28) / 4];
    void (*ClassConstructor)(void *);       // +0x104
};

// Versus object iterator: the array pointer and the current index.
class FObjectIterator
{
public:
    FObjectIterator();                      // RVA 0x1f470
    ~FObjectIterator();                     // folded empty function, RVA 0x4a550
    void operator++()
    {
        while (++Index < Array->Num() && !(*Array)(Index))
            ;
    }
    operator UBOOL() { return Index < Array->Num(); }
    UObject *operator*() { return (*Array)(Index); }
    UObject *operator->() { return (*Array)(Index); }
protected:
    TArray<UObject *> *Array;
    INT Index;
};

// The same iterator without the out-of-line destructor; its constructor is
// expanded in place by the link.
class FRawObjectIterator
{
public:
    FRawObjectIterator();
    void operator++()
    {
        while (++Index < Array->Num() && !(*Array)(Index))
            ;
    }
    operator UBOOL() { return Index < Array->Num(); }
    UObject *operator->() { return (*Array)(Index); }
protected:
    TArray<UObject *> *Array;
    INT Index;
};

FRawObjectIterator::FRawObjectIterator()
    : Array(&UObject::GObjObjects), Index(-1)
{
    ++*this;
}

// RVA 0x1d6f0
__declspec(noinline) UObject *UObject::StaticConstructObject(UClass *InClass, UObject *InOuter, FName InName, DWORD SetFlags,
                                        UObject *InTemplate, FOutputDevice *Error, UObject *SubobjectRoot)
{
    UObject *Result = StaticAllocateObject(InClass, InOuter, InName, SetFlags, InTemplate, Error, 0, SubobjectRoot);
    if (Result)
        (*InClass->ClassConstructor)(Result);
    return Result;
}

// RVA 0x1d730
void UObject::SerializeRootSet(FArchive &Ar, DWORD KeepFlags, DWORD RequiredFlags)
{
    UObject *Obj;
    Ar << GObjRoot;
    for (FObjectIterator It; It; ++It)
        if ((It->GetFlags() & KeepFlags) && (It->GetFlags() & RequiredFlags) == RequiredFlags)
        {
            Obj = *It;
            Ar << Obj;
        }
}

// RVA 0x1d7c0
void CompactObjects_1d7c0()
{
    // An unused local array; only its construction and destruction remain.
    TArray<INT> Unused;
    INT j = 0;
    for (INT i = 0; i < UObject::GObjObjects.Num(); i++) {
        UObject *Obj = UObject::GObjObjects(i);
        if (Obj) {
            Obj->Index = j;
            UObject::GObjObjects(j++) = Obj;
        }
    }
    UObject::GObjObjects.Remove(j, UObject::GObjObjects.Num() - j);
    UObject::GObjObjects.Shrink();
    UObject::GObjAvailable.Empty();
}

extern INT GGarbageRefCount;               // 0x10c925fc

class FArchiveTagUsed : public FArchive
{
public:
    FArchiveTagUsed();
    void *Context;
};

// RVA 0x1d8d0
FArchiveTagUsed::FArchiveTagUsed()
    : Context(0)
{
    GGarbageRefCount = 0;

    // Tag all objects as unreachable.
    for (FRawObjectIterator It; It; ++It)
        It->SetFlags(RF_Unreachable | RF_TagGarbage);

    // Tag all names as unreachable.
    for (INT n = 0; n < FName_Names.Num(); n++)
        if (FName_Names(n))
            FName_Names(n)->Flags |= RF_Unreachable;
}

FArchive &SerializeIndex(FArchive &Ar, INT &Value);   // RVA 0x1ea40

// RVA 0xf85a0: operator<<(FArchive&, TArray<UObject*>&), the TArray
// serializer instantiated for object arrays (Ar in EAX, the array in EBX).
// It lives outside this item's range but is defined here so the call in
// SerializeRootSet gets its whole-program convention; it matches on its own.
__declspec(noinline) FArchive &operator<<(FArchive &Ar, TArray<UObject *> &A)
{
    Ar.CountBytes(A.ArrayNum * sizeof(UObject *), A.ArrayMax * sizeof(UObject *));
    if (Ar.ArIsLoading) {
        INT NewNum;
        SerializeIndex(Ar, NewNum);
        A.Empty(sizeof(UObject *), NewNum);
        for (INT i = 0; i < NewNum; i++)
            Ar << A(A.FArray::Add(1, sizeof(UObject *)));
    } else {
        SerializeIndex(Ar, A.ArrayNum);
        for (INT i = 0; i < A.ArrayNum; i++)
            Ar << A(i);
    }
    return Ar;
}

// Scaffolding for the link, not part of the unit. The callees retail reaches
// through whole-program conventions are defined here so the link gives them
// those conventions; their own retail code is matched elsewhere.
void Escape(void *);
__declspec(noinline) FObjectIterator::FObjectIterator()
    : Array(&UObject::GObjObjects), Index(-1)
{
    ++*this;
}
__declspec(noinline) FObjectIterator::~FObjectIterator()
{
    Escape(0);
}
// Stand-in for the compact index serializer (RVA 0x1ea40).
__declspec(noinline) FArchive &SerializeIndex(FArchive &Ar, INT &Value)
{
    if (!Ar.ArIsLoading && !Ar.ArIsSaving) {
        Ar.Serialize(&Value, sizeof(INT));
        return Ar;
    }
    DWORD V = Value >= 0 ? Value : -Value;
    unsigned char B0 = (unsigned char)((Value >= 0 ? 0 : 0x80) + (V < 0x40 ? V : (V & 0x3f) + 0x40));
    Value = 0;
    Ar.Serialize(&B0, 1);
    if (B0 & 0x40) {
        V >>= 6;
        unsigned char B1 = (unsigned char)(V < 0x80 ? V : (V & 0x7f) + 0x80);
        Ar.Serialize(&B1, 1);
        if (B1 & 0x80) {
            V >>= 7;
            unsigned char B2 = (unsigned char)(V < 0x80 ? V : (V & 0x7f) + 0x80);
            Ar.Serialize(&B2, 1);
            if (B2 & 0x80) {
                V >>= 7;
                unsigned char B3 = (unsigned char)(V < 0x80 ? V : (V & 0x7f) + 0x80);
                Ar.Serialize(&B3, 1);
                if (B3 & 0x80) {
                    V >>= 7;
                    unsigned char B4 = (unsigned char)V;
                    Ar.Serialize(&B4, 1);
                    Value = B4;
                }
                Value = (Value << 7) + (B3 & 0x7f);
            }
            Value = (Value << 7) + (B2 & 0x7f);
        }
        Value = (Value << 7) + (B1 & 0x7f);
    }
    Value = (Value << 6) + (B0 & 0x3f);
    if (B0 & 0x80)
        Value = -Value;
    return Ar;
}
inline void *operator new(unsigned int, void *Mem) { return Mem; }
UObject *Driver_1d6f0(UClass *C, UObject *O, FName N, DWORD F, UObject *T, FOutputDevice *E, UObject *R)
{
    // Several call sites keep it out of line, as in retail.
    Escape(UObject::StaticConstructObject(C, O, N, F, T, E, R));
    Escape(UObject::StaticConstructObject(C, O, N, F | 1, T, E, R));
    Escape(UObject::StaticConstructObject(C, 0, N, F, 0, E, 0));
    return UObject::StaticConstructObject(C, O, N, F, T, E, R);
}
void Driver_1d730(FArchive &Ar, DWORD K, DWORD R)
{
    Escape(&UObject::GObjObjects); Escape(&UObject::GObjRoot);
    Escape((void *)&UObject::SerializeRootSet);
    UObject::SerializeRootSet(Ar, K, R);
}
void Driver_1d7c0()
{
    Escape(&GMalloc); Escape(&UObject::GObjObjects); Escape(&UObject::GObjAvailable);
    CompactObjects_1d7c0();
}
void Driver_1d8d0(void *Mem)
{
    Escape(&UObject::GObjObjects); Escape(&FName_Names); Escape(&GGarbageRefCount);
    new (Mem) FArchiveTagUsed;
}
