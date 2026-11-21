// Work item 0246: Versus RVA 0x5aba0-0x5adcb. TMap<UObject*,...> lookups and
// rehash, plus TArray helpers. All link-time optimised (/GL + /LTCG): callers
// pass the object and arguments in registers.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

class FMalloc
{
public:
    virtual void* Malloc(DWORD Count, const TCHAR* Tag);
    virtual void* Realloc(void* Original, DWORD Count, const TCHAR* Tag);
    virtual void Free(void* Original);
};
extern FMalloc* GMalloc;                      // 0x10c73bf0
inline void* appMalloc(DWORD Count, const TCHAR* Tag) { return GMalloc->Malloc(Count, Tag); }
inline void appFree(void* Original) { GMalloc->Free(Original); }
extern const TCHAR HashMapHashTag[];          // 0x10c7495c, TEXT("HashMapHash")

inline void* operator new(unsigned int, void* Mem) { return Mem; }

class UObject
{
public:
    virtual ~UObject();
    INT Index;
    INT GetIndex() const { return Index; }
};

inline DWORD GetTypeHash(const UObject* A) { return A ? A->GetIndex() : 0; }

class FArray
{
public:
    void* Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Add(INT Count, INT ElementSize);      // RVA 0x44e0
    void Empty(INT ElementSize, INT Slack);   // RVA 0x4550
};

// TMap<UObject*,INT> pair (12 bytes).
struct FObjectPair
{
    INT HashNext;
    UObject* Key;
    INT Value;
};

class FObjectPairArray : public FArray
{
public:
    FObjectPair& operator()(INT i) { return ((FObjectPair*)Data)[i]; }
    const FObjectPair& operator()(INT i) const { return ((FObjectPair*)Data)[i]; }
    FObjectPairArray& operator=(const FObjectPairArray& Other);
};

inline void* operator new(unsigned int, FObjectPairArray& Array)
{
    INT Index = Array.FArray::Add(1, sizeof(FObjectPair));
    return &((FObjectPair*)Array.Data)[Index];
}

// TMap<UObject*,INT>; the class name is not recovered.
class FObjectMap
{
public:
    FObjectPairArray Pairs;
    INT* Hash;
    INT HashCount;

    INT FindRef(UObject* const& Key);
    INT* Find(UObject* const& Key);
    void Rehash();
};

#pragma auto_inline(off)
// RVA 0x5aba0
INT FObjectMap::FindRef(UObject* const& Key)
{
    UObject* K = Key;
    for (INT i = Hash[GetTypeHash(K) & (HashCount - 1)]; i != -1; )
    {
        FObjectPair& Pair = Pairs(i);
        if (Pair.Key == K)
            return Pair.Value;
        i = Pair.HashNext;
    }
    return 0;
}

// RVA 0x5abe0
INT* FObjectMap::Find(UObject* const& Key)
{
    for (INT i = Hash[GetTypeHash(Key) & (HashCount - 1)]; i != -1; i = Pairs(i).HashNext)
        if (Pairs(i).Key == Key)
            return &Pairs(i).Value;
    return 0;
}

// RVA 0x5aca0
void FObjectMap::Rehash()
{
    INT* NewHash = (INT*)appMalloc(HashCount * sizeof(INT), HashMapHashTag);
    INT i;
    for (i = 0; i < HashCount; i++)
        NewHash[i] = -1;
    for (i = 0; i < Pairs.ArrayNum; i++)
    {
        FObjectPair& Pair = Pairs(i);
        INT iHash = GetTypeHash(Pair.Key) & (HashCount - 1);
        Pair.HashNext = NewHash[iHash];
        NewHash[iHash] = i;
    }
    if (Hash)
        appFree(Hash);
    Hash = NewHash;
}

// RVA 0x5ad70
FObjectPairArray& FObjectPairArray::operator=(const FObjectPairArray& Other)
{
    if (this != &Other)
    {
        Empty(sizeof(FObjectPair), Other.ArrayNum);
        for (INT i = 0; i < Other.ArrayNum; i++)
            new(*this) FObjectPair(Other(i));
    }
    return *this;
}

class FString
{
public:
    TCHAR* Data;
    INT ArrayNum;
    INT ArrayMax;
    ~FString();                               // RVA 0x48b0
    FString& operator=(const FString& Other); // RVA 0x4640
};

// A 0x44-byte record with a string first; names not recovered.

struct FRecordQuad
{
    INT A, B, C, D;
};

struct FRecord_5ac30
{
    FString Name;
    INT V0C;
    INT V10;
    FRecordQuad Quad;
    INT V24, V28, V2C, V30, V34, V38, V3C, V40;

    ~FRecord_5ac30();
    FRecord_5ac30& operator=(const FRecord_5ac30& Other);
};

// RVA 0x179000: only destroys Name (a tail jump to FString::~FString).
FRecord_5ac30::~FRecord_5ac30()
{
}

// RVA 0x5ac30
FRecord_5ac30& FRecord_5ac30::operator=(const FRecord_5ac30& Other)
{
    Name = Other.Name;
    V0C = Other.V0C;
    V10 = Other.V10;
    Quad = Other.Quad;
    V24 = Other.V24;
    V28 = Other.V28;
    V2C = Other.V2C;
    V30 = Other.V30;
    V34 = Other.V34;
    V38 = Other.V38;
    V3C = Other.V3C;
    V40 = Other.V40;
    return *this;
}

#pragma auto_inline(on)

class FRecordArray : public FArray
{
public:
    void Empty(INT Slack);
};

#pragma auto_inline(off)
// RVA 0x5ad30
void FRecordArray::Empty(INT Slack)
{
    for (INT i = 0; i < ArrayNum; i++)
        ((FRecord_5ac30*)Data)[i].FRecord_5ac30::~FRecord_5ac30();
    FArray::Empty(sizeof(FRecord_5ac30), Slack);
}
#pragma auto_inline(on)


// Scaffolding for the link, not part of the unit.
void Escape(void*);
void Use(INT);
struct FMapOwner_5aba0
{
    char Pad[0x34];
    FObjectMap Map;
    INT Lookup(UObject* Key) { INT V = Map.FindRef(Key); if (V) Use(V); return V; }
};
extern "C" INT Driver_5aba0(FMapOwner_5aba0* O, UObject* K) { return O->Lookup(K); }
extern "C" INT* Driver_5abe0(FObjectMap* M, UObject** K) { return M->Find(*K); }
extern "C" void Driver_5aca0(FObjectMap* M) { Escape(&GMalloc); M->Rehash(); }
extern "C" FObjectPairArray* Driver_5ad70(FObjectPairArray* A, FObjectPairArray* B) { return &(*A = *B); }
extern "C" FRecord_5ac30* Driver_5ac30(FRecord_5ac30* A, FRecord_5ac30* B) { return &(*A = *B); }
extern "C" void Driver_5ad30(FRecordArray* A, FRecordArray* B, INT S)
{
    A->Empty(S); Use(1); B->Empty(0); Use(2); A->Empty(B->ArrayNum); Use(3); B->Empty(S + 1);
}
