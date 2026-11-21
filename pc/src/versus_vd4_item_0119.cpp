// Work item 0119: Versus RVA 0x1f430-0x1f5cb.
// An object-array iterator (UObject::GObjObjects style) and a
// TMap<UObject*, 8-byte value> instantiation, all LTCG (register conventions).
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FArray();
    INT Add(INT Count, INT ElementSize);     // retail 0x44e0 (@add_array@12)
    INT Num() const { return ArrayNum; }
};

template<class T> class TArray : public FArray
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    __declspec(noinline) INT AddItem(const T &Item)
    {
        INT Index = FArray::Add(1, sizeof(T));
        (*this)(Index) = Item;
        return Index;
    }
};

class UClass;
class UObject
{
public:
    void *VfTableHolder;   // stands in for the vtable pointer
    INT Index;             // +0x04
    UObject *HashNext;
    void *StateFrame;
    void *_Linker;
    INT _LinkerIndex;
    UObject *Outer;
    DWORD ObjectFlags;
    INT Name;              // FName
    UClass *Class;         // +0x24
    inline INT IsA(UClass *SomeBase) const;
};
class UField : public UObject
{
public:
    UField *SuperField;    // +0x28
    UField *Next;
};
class UClass : public UField {};

inline INT UObject::IsA(UClass *SomeBase) const
{
    for (UClass *TempClass = Class; TempClass; TempClass = (UClass *)TempClass->SuperField)
        if (TempClass == SomeBase)
            return 1;
    return 0;
}

// UObject::GObjObjects.
extern TArray<UObject *> GObjObjects;
// Neutral name: a static UClass object (address 0x10cc9b18) whose class is
// not yet identified.
extern UClass UnnamedClass_cc9b18;

// Iterator over the object array; the class-filtered form is a separate
// instantiation.
struct FObjectArrayIterator
{
    TArray<UObject *> *Array;
    INT Index;
    __declspec(noinline) FObjectArrayIterator() : Array(&GObjObjects), Index(-1) { ++*this; }
    void operator++()
    {
        while (++Index < Array->Num() && !(*Array)(Index))
            ;
    }
};
struct FClassObjectIterator
{
    TArray<UObject *> *Array;
    INT Index;
    FClassObjectIterator &operator++();
};

// RVA 0x1f430 (this in EAX)
__declspec(noinline) FClassObjectIterator &FClassObjectIterator::operator++()
{
    while (++Index < Array->Num()
           && (!(*Array)(Index) || !(*Array)(Index)->IsA(&UnnamedClass_cc9b18)))
        ;
    return *this;
}

// RVA 0x1f470 is FObjectArrayIterator::FObjectArrayIterator (this in EAX).

// ---- TMap<UObject*, FUnnamedValue_8> ----
struct FUnnamedValue_8 { INT A, B; };

inline DWORD GetTypeHash(const UObject *A) { return A ? A->Index : 0; }

struct TPair
{
    INT HashNext;
    UObject *Key;
    FUnnamedValue_8 Value;
    TPair(UObject *const &InKey, const FUnnamedValue_8 &InValue) : Key(InKey), Value(InValue) {}
};
// Neutral 16-byte record appended at 0x1f5a0.
struct FUnnamedRecord_16 { INT A, B, C, D; };

class FObjectValueMap
{
public:
    TArray<TPair> Pairs;
    INT *Hash;
    INT HashCount;

    FObjectValueMap() : Hash(0), HashCount(8) { Rehash(); }
    void Rehash();
    FUnnamedValue_8 &Add(UObject *const &InKey, const FUnnamedValue_8 &InValue);
    FUnnamedValue_8 &Set(UObject *const &InKey, const FUnnamedValue_8 &InValue);
    FUnnamedValue_8 *Find(UObject *const &Key);
};

// RVA 0x1f4f0 (this in ECX, key in EBX, value in EDI)
__declspec(noinline) FUnnamedValue_8 &FObjectValueMap::Set(UObject *const &InKey, const FUnnamedValue_8 &InValue)
{
    INT i = Hash[GetTypeHash(InKey) & (HashCount - 1)];
    while (i != -1) {
        TPair &Pair = Pairs(i);
        if (Pair.Key == InKey) {
            Pair.Value = InValue;
            return Pair.Value;
        }
        i = Pair.HashNext;
    }
    return Add(InKey, InValue);
}

// RVA 0x1f550 (this in ECX, key in EAX)
__declspec(noinline) FUnnamedValue_8 *FObjectValueMap::Find(UObject *const &Key)
{
    for (INT i = Hash[GetTypeHash(Key) & (HashCount - 1)]; i != -1; i = Pairs(i).HashNext)
        if (Pairs(i).Key == Key)
            return &Pairs(i).Value;
    return 0;
}

// RVA 0x1f4a0 is FObjectValueMap::FObjectValueMap; RVA 0x1f5a0 is
// TArray<FUnnamedRecord_16>::AddItem (this in EDI, item in ESI).

// Scaffolding for the link, not part of the unit: retail 0x1f8b0 (Rehash,
// unverified) and 0x1f940 (Add, also matches retail) are defined here so the
// LTCG linker gives them their register conventions.
inline void *operator new(unsigned int, void *Mem) { return Mem; }
__declspec(noinline) void FObjectValueMap::Rehash()
{
    INT *NewHash = (INT *)GMalloc->Malloc(HashCount * sizeof(INT), L"HashMapHash");
    INT i;
    for (i = 0; i < HashCount; i++)
        NewHash[i] = -1;
    for (i = 0; i < Pairs.Num(); i++) {
        TPair &Pair = Pairs(i);
        INT iHash = GetTypeHash(Pair.Key) & (HashCount - 1);
        Pair.HashNext = NewHash[iHash];
        NewHash[iHash] = i;
    }
    if (Hash)
        GMalloc->Free(Hash);
    Hash = NewHash;
}
inline void *operator new(unsigned int Size, FArray &Array)
{
    INT Index = Array.Add(1, Size);
    return (char *)Array.Data + Index * Size;
}
__declspec(noinline) FUnnamedValue_8 &FObjectValueMap::Add(UObject *const &InKey, const FUnnamedValue_8 &InValue)
{
    TPair &Pair = *new(Pairs) TPair(InKey, InValue);
    INT iHash = GetTypeHash(Pair.Key) & (HashCount - 1);
    Pair.HashNext = Hash[iHash];
    Hash[iHash] = Pairs.Num() - 1;
    if (HashCount * 2 + 8 < Pairs.Num()) {
        HashCount *= 2;
        Rehash();
    }
    return Pair.Value;
}
void Escape(void *);
INT Test(UObject *);
struct FClassObjectIteratorUse : FClassObjectIterator
{
    __declspec(noinline) FClassObjectIteratorUse() { Array = &GObjObjects; Index = -1; ++*this; }
    UObject *operator*() { return (*Array)(Index); }
    operator INT() { return Index < Array->Num(); }
};
struct FUnnamedSink { void Take(UObject *Obj); };
void Driver_1f430(FUnnamedSink *Sink)
{
    for (FClassObjectIteratorUse It; It; ++It)
        Sink->Take(*It);
}
void Driver_1f470()
{
    FObjectArrayIterator It; Escape(&It);
    FObjectArrayIterator It2; Escape(&It2);
    FObjectArrayIterator It3; Escape(&It3);
}
void Driver_1f4a0(void *Mem) { Escape(new(Mem) FObjectValueMap); }
extern FObjectValueMap GMap1; extern UObject *GKeys[16]; extern FUnnamedValue_8 GVals[16];
// Mirrors the single retail caller at 0x185a0 (an archive visiting objects).
void SerializeObject(UObject *Obj, void *Ar);
struct FUnnamedArchive_185a0
{
    char Pad[0x3c];
    FObjectValueMap *Map;
    INT Depth;
    UObject *Parent;
    virtual FUnnamedArchive_185a0 &Visit(UObject *&Obj);
};
FUnnamedArchive_185a0 &FUnnamedArchive_185a0::Visit(UObject *&Obj)
{
    UObject *O = Obj;
    if (O) {
        FUnnamedValue_8 *V = Map->Find(O);
        if (!V || Depth < V->A) {
            FUnnamedValue_8 NV;
            NV.A = Depth;
            NV.B = (INT)Parent;
            Map->Set(O, NV);
        }
        if (O->ObjectFlags & 0x10) {
            O->ObjectFlags &= ~0x10;
            UObject *SavedParent = Parent;
            Depth++;
            Parent = O;
            SerializeObject(O, this);
            Depth--;
            Parent = SavedParent;
        }
    }
    return *this;
}
void Driver_1f4f0(FUnnamedArchive_185a0 *Ar, UObject **Obj) { Escape(&Ar->Visit(*Obj)); }
void Driver_1f550(FObjectValueMap *M, UObject *const *K)
{
    Escape(M->Find(*K)); Escape(M->Find(K[1])); Escape(M->Find(K[2]));
}
void Driver_1f5a0(TArray<FUnnamedRecord_16> *A, const FUnnamedRecord_16 *R)
{
    A->AddItem(*R); A->AddItem(R[1]); A->AddItem(R[2]);
}
