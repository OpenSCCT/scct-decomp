// Work item 0121: Versus RVA 0x1f8b0-0x1f9b9.
// TMap<UObject*, V>::Rehash and TMap::Add, where V is an 8-byte value
// (two dwords; its real type is unknown, so it is named FUnnamedValue_1f940).
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

class UObject
{
public:
    virtual ~UObject();
    INT Index;
    INT GetIndex() const { return Index; }
};
inline DWORD GetTypeHash(const UObject *A) { return A ? A->GetIndex() : 0; }

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Add(INT Count, INT ElementSize);   // retail 0x44e0
    INT Num() const { return ArrayNum; }
};
inline void *operator new(unsigned int, void *Mem) { return Mem; }
inline void *operator new[](unsigned int Size, const TCHAR *Tag) { return GMalloc->Malloc(Size, Tag); }

struct FUnnamedValue_1f940
{
    INT A;
    INT B;
};

struct TPair
{
    INT HashNext;
    UObject *Key;
    FUnnamedValue_1f940 Value;
    TPair(UObject *const &InKey, const FUnnamedValue_1f940 &InValue)
        : Key(InKey), Value(InValue) {}
};

class TObjectMap
{
public:
    FArray Pairs;      // TArray<TPair>
    INT *Hash;
    INT HashCount;

    void Rehash();
    FUnnamedValue_1f940 &Add(UObject *const &InKey, const FUnnamedValue_1f940 &InValue);
    TPair *PairData() const { return (TPair *)Pairs.Data; }
};

// RVA 0x1f8b0 (LTCG: this in ESI)
void TObjectMap::Rehash()
{
    INT *NewHash = new(L"HashMapHash") INT[HashCount];
    INT i;
    for (i = 0; i < HashCount; i++)
        NewHash[i] = -1;
    for (i = 0; i < Pairs.Num(); i++) {
        TPair &Pair = PairData()[i];
        INT iHash = GetTypeHash(Pair.Key) & (HashCount - 1);
        Pair.HashNext = NewHash[iHash];
        NewHash[iHash] = i;
    }
    if (Hash)
        GMalloc->Free(Hash);
    Hash = NewHash;
}

// RVA 0x1f940 (LTCG: this in ECX, InValue in EAX, InKey on the stack)
FUnnamedValue_1f940 &TObjectMap::Add(UObject *const &InKey, const FUnnamedValue_1f940 &InValue)
{
    TPair &Pair = *new((TPair *)Pairs.Data + Pairs.Add(1, sizeof(TPair))) TPair(InKey, InValue);
    INT iHash = GetTypeHash(Pair.Key) & (HashCount - 1);
    Pair.HashNext = Hash[iHash];
    Hash[iHash] = Pairs.Num() - 1;
    if (HashCount * 2 + 8 < Pairs.Num()) {
        HashCount *= 2;
        Rehash();
    }
    return Pair.Value;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_1f940(TObjectMap *M, UObject **K, FUnnamedValue_1f940 *V) { Escape(&GMalloc); Escape(&M->Add(*K, *V)); }
void Driver_1f8b0(TObjectMap *M) { Escape(&GMalloc); M->Rehash(); }
