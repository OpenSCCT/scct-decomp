// Work item 0103: Versus RVA 0x18280-0x18596 (LTCG objects).
// The archive base layout (ArVer 0xaf, ArNetVer 2000, ...) is FArchive; the
// derived classes (vtables 0x10c0ce00 and 0x10c0cda0) are unlabelled, so they
// carry neutral names.
typedef int INT;
typedef unsigned long DWORD;
typedef unsigned int size_t;
typedef DWORD UBOOL;

inline void *operator new(size_t, void *Mem) { return Mem; }

class FArchive
{
public:
    INT ArVer, ArNetVer, ArLicenseeVer, ArIsLoading, ArIsSaving, ArIsTrans, ArIsPersistent;
    INT ArForEdit, ArForClient, ArForServer, ArIsError, ArIsCriticalError, ArContainsCode;
    INT ArFlags3, ArMaxSerializeSize;
    FArchive()
        : ArVer(0xaf), ArNetVer(2000), ArLicenseeVer(0), ArIsLoading(0), ArIsSaving(0),
          ArIsTrans(0), ArIsPersistent(0), ArForEdit(1), ArForClient(1), ArForServer(1),
          ArIsError(0), ArIsCriticalError(0), ArContainsCode(3), ArFlags3(0), ArMaxSerializeSize(-1)
    {}
    virtual ~FArchive() {}
};

class UObject
{
public:
    virtual void Slot00();
    virtual void Slot04();
    virtual void Slot08();
    virtual void Slot0c();
    virtual void Slot10();
    virtual void Slot14();
    virtual void Slot18();
    virtual void Slot1c();
    virtual void Slot20();
    virtual void Slot24();
    virtual void Serialize(FArchive &Ar); // +0x28
    INT Index;
    UObject *HashNext;
    void *StateFrame;
    void *_Linker;
    INT _LinkerIndex;
    UObject *Outer;
    DWORD ObjectFlags;
    static void SerializeRootSet(FArchive &Ar, DWORD KeepFlags, DWORD RequiredFlags);
};

struct FObjectArray
{
    UObject **Data;
    INT ArrayNum;
};
// UObject::GObjObjects. Declared extern "C" only so the verifier's stub layout
// does not place another stub at GObjObjects+4 (ArrayNum).
extern "C" FObjectArray GObjObjects;

// Simplified object iterator (no class filter).
struct FRawObjectIterator
{
    FObjectArray *Objects;
    INT Index;
    FRawObjectIterator() : Objects(&GObjObjects), Index(-1) { ++*this; }
    void operator++() { while (++Index < Objects->ArrayNum && !Objects->Data[Index]); }
    operator int() { return Index < Objects->ArrayNum; }
    UObject *operator->() { return Objects->Data[Index]; }
};

// RVA 0x18280: archive that reads an object (vtable 0x10c0ce00).
class FArchiveUnnamed_18280 : public FArchive
{
public:
    INT Param;
    INT Extra;
    FArchiveUnnamed_18280(UObject *Src, INT InParam);
    virtual ~FArchiveUnnamed_18280();
};

FArchiveUnnamed_18280::FArchiveUnnamed_18280(UObject *Src, INT InParam)
    : Param(InParam), Extra(0)
{
    Src->Serialize(*this);
}

// RVA 0x18480: archive that walks the root set (vtable 0x10c0cda0).
class FArchiveUnnamed_18480 : public FArchive
{
public:
    void *Map;
    INT A;
    INT B;
    FArchiveUnnamed_18480(void *InMap);
    virtual ~FArchiveUnnamed_18480() {}
};

FArchiveUnnamed_18480::FArchiveUnnamed_18480(void *InMap)
    : Map(InMap), A(0), B(0)
{
    for (FRawObjectIterator It; It; ++It)
        It->ObjectFlags |= 0x10;
    UObject::SerializeRootSet(*this, 0x4000000, 0);
    for (FRawObjectIterator It2; It2; ++It2)
        It2->ObjectFlags &= ~0x10;
}

// Engine containers used by RVA 0x18330.
typedef unsigned short TCHAR;
class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;
void *appMemcpy(void *Dest, const void *Src, INT Count);
extern const TCHAR FArrayTag[]; // L"FArray" (shared literal)

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    FArray(INT InNum, INT ElementSize) : ArrayNum(InNum), ArrayMax(InNum)
    {
        Data = ArrayMax ? GMalloc->Malloc(ArrayMax * ElementSize, FArrayTag) : 0;
    }
    ~FArray()
    {
        if (Data)
            GMalloc->Free(Data);
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
    INT Add(INT Count, INT ElementSize);
    void Insert(INT Index, INT Count, INT ElementSize);
    void Realloc(INT ElementSize);
    void Remove(INT Index, INT Count, INT ElementSize);
};

extern "C" void *memmove(void *, const void *, size_t);
#pragma intrinsic(memmove)
__declspec(noinline) void FArray::Insert(INT Index, INT Count, INT ElementSize)
{
    INT OldNum = ArrayNum;
    if ((ArrayNum += Count) > ArrayMax) {
        ArrayMax = ArrayNum + 3 * ArrayNum / 8 + 32;
        Realloc(ElementSize);
    }
    memmove((unsigned char *)Data + (Index + Count) * ElementSize,
            (unsigned char *)Data + Index * ElementSize,
            (OldNum - Index) * ElementSize);
}

template <class T> class TArray : public FArray
{
public:
    TArray() {}
    TArray(const TArray &Other);
    ~TArray();
    T &operator()(INT i) { return ((T *)Data)[i]; }
    INT AddItem(const T &Item)
    {
        INT Index = Add(1, sizeof(T));
        (*this)(Index) = Item;
        return Index;
    }
    void InsertItem(INT Index, const T &Item)
    {
        Insert(Index, 1, sizeof(T));
        (*this)(Index) = Item;
    }
};

template <class T> __declspec(noinline) TArray<T>::TArray(const TArray<T> &Other)
    : FArray(Other.ArrayNum, sizeof(T))
{
    appMemcpy(Data, Other.Data, ArrayNum * sizeof(T));
}
template <class T> __declspec(noinline) TArray<T>::~TArray()
{
    Remove(0, ArrayNum, sizeof(T));
}

inline DWORD GetTypeHash(const UObject *O) { return O ? O->Index : 0; }

// Value stored per object while walking references (layout only).
struct FReferenceLink
{
    UBOOL Linked;
    UObject *Referencer;
};

class FReferenceMap
{
public:
    struct TPair
    {
        INT HashNext;
        UObject *Key;
        FReferenceLink Value;
    };
    TArray<TPair> Pairs;
    INT *Hash;
    INT HashCount;
    FReferenceMap();
    ~FReferenceMap();
    FReferenceLink *Find(UObject *const &Key)
    {
        for (INT i = Hash[GetTypeHash(Key) & (HashCount - 1)]; i != -1; i = Pairs(i).HashNext)
            if (Pairs(i).Key == Key)
                return &Pairs(i).Value;
        return 0;
    }
    const FReferenceLink *Find(UObject *const &Key) const;
};
__declspec(noinline) const FReferenceLink *FReferenceMap::Find(UObject *const &Key) const
{
    for (INT i = Hash[GetTypeHash(Key) & (HashCount - 1)]; i != -1; i = ((TPair *)Pairs.Data)[i].HashNext)
        if (((TPair *)Pairs.Data)[i].Key == Key)
            return &((TPair *)Pairs.Data)[i].Value;
    return 0;
}
void Rehash_Stub(FReferenceMap *M);
__declspec(noinline) FReferenceMap::FReferenceMap() : Hash(0), HashCount(8) { Rehash_Stub(this); }
__declspec(noinline) FReferenceMap::~FReferenceMap() { Rehash_Stub(this); }

// RVA 0x18330: the chain of referencers from the root set down to Obj.
TArray<UObject *> FindReferenceChain_18330(UObject *Obj)
{
    UObject *Current = Obj;
    FReferenceMap Map;
    FArchiveUnnamed_18480 Ar(&Map);
    TArray<UObject *> Chain;
    const FReferenceMap &ConstMap = Map;
    if (ConstMap.Find(Obj)) {
        Chain.AddItem(Current);
        FReferenceLink *Link;
        while ((Link = Map.Find(Current))->Linked) {
            Current = Link->Referencer;
            Chain.InsertItem(0, Current);
        }
    }
    return Chain;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_18280(void *Mem, UObject *Src, INT P)
{
    new (Mem) FArchiveUnnamed_18280(Src, P);
}
void Driver_18480(void *Mem, void *Map)
{
    Escape(&GObjObjects);
    new (Mem) FArchiveUnnamed_18480(Map);
}
void Driver_18330(UObject *O, TArray<UObject *> *Out)
{
    *Out = FindReferenceChain_18330(O);
}
