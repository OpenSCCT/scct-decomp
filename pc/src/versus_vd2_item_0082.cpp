// Work item 0082: TMap<FString,FString> helpers (Unreal Engine 2 UnTemplate.h).
// Pair layout (0x1c bytes): HashNext, FString Key, FString Value.
// Map layout: TArray<TPair> Pairs (+0), INT* Hash (+0xc), INT HashCount (+0x10).
// These functions come from an LTCG object (custom calling conventions).

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

DWORD appStrihash(const TCHAR *Data);
extern const TCHAR EmptyString[];   // L"" shared in retail

inline void *operator new(unsigned int Size, void *Mem) { return Mem; }

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;

    INT Add(INT Count, INT ElementSize);
    void Empty(INT ElementSize, INT Slack);
    void Remove(INT Index, INT Count, INT ElementSize);
    ~FArray()
    {
        if (Data)
        {
            GMalloc->Free(Data);
            Data = 0;
        }
        ArrayNum = ArrayMax = 0;
    }
};

class FString : public FArray
{
public:
    FString(const TCHAR *In);
    ~FString();
    const TCHAR *operator*() const { return ArrayNum ? (const TCHAR *)Data : EmptyString; }
};

inline DWORD GetTypeHash(const FString &S) { return appStrihash(*S); }

struct TPair
{
    INT HashNext;
    FString Key;
    FString Value;
    TPair(const TCHAR *InKey, const TCHAR *InValue);
    ~TPair();
};

class TPairArray : public FArray
{
public:
    TPair &operator()(INT i) { return ((TPair *)Data)[i]; }
    void Remove(INT Index, INT Count);
    void Empty(INT Slack);
    ~TPairArray() { Remove(0, ArrayNum); }
};

class TMapFString
{
public:
    TPairArray Pairs;
    INT *Hash;
    INT HashCount;

    void Rehash();
    FString &Add(const TCHAR *InKey, const TCHAR *InValue);
};

// RVA 0x14900: TMap<FString,FString>::Add
FString &TMapFString::Add(const TCHAR *InKey, const TCHAR *InValue)
{
    TPair &Pair = *new(&((TPair *)Pairs.Data)[Pairs.Add(1, sizeof(TPair))]) TPair(InKey, InValue);
    INT iHash = GetTypeHash(Pair.Key) & (HashCount - 1);
    Pair.HashNext = Hash[iHash];
    Hash[iHash] = Pairs.ArrayNum - 1;
    if (HashCount * 2 + 8 < Pairs.ArrayNum)
    {
        HashCount *= 2;
        Rehash();
    }
    return Pair.Value;
}

// RVA 0x149f0: TArray<TPair>::Empty (noinline: retail kept it out of line)
__declspec(noinline) void TPairArray::Empty(INT Slack)
{
    for (INT i = 0; i < ArrayNum; i++)
        (&(*this)(i))->~TPair();
    FArray::Empty(sizeof(TPair), Slack);
}

// Scaffolding for the link, not part of the unit: callees given bodies so the
// linker sees them inside the LTCG module, as retail did.
extern DWORD GCRCTable[256];
TCHAR appToUpper(TCHAR c);
DWORD appStrihash(const TCHAR *Data)
{
    DWORD Hash = 0;
    while (*Data)
    {
        TCHAR Ch = appToUpper(*Data++);
        unsigned char B = (unsigned char)Ch;
        Hash = ((Hash >> 8) & 0x00FFFFFF) ^ GCRCTable[(Hash ^ B) & 0x000000FF];
        B = (unsigned char)(Ch >> 8);
        Hash = ((Hash >> 8) & 0x00FFFFFF) ^ GCRCTable[(Hash ^ B) & 0x000000FF];
    }
    return Hash;
}
__declspec(noinline) void TPairArray::Remove(INT Index, INT Count)
{
    for (INT i = Index; i < Index + Count; i++)
        (&(*this)(i))->~TPair();
    FArray::Remove(Index, Count, sizeof(TPair));
}
TPair::~TPair() {}
TPair::TPair(const TCHAR *InKey, const TCHAR *InValue) : Key(InKey), Value(InValue) {}
void TMapFString::Rehash()
{
    INT *NewHash = (INT *)GMalloc->Malloc(HashCount * sizeof(INT), 0);
    INT i;
    for (i = 0; i < HashCount; i++)
        NewHash[i] = -1;
    for (i = 0; i < Pairs.ArrayNum; i++)
    {
        TPair &Pair = Pairs(i);
        INT iHash = GetTypeHash(Pair.Key) & (HashCount - 1);
        Pair.HashNext = NewHash[iHash];
        NewHash[iHash] = i;
    }
    if (Hash)
        GMalloc->Free(Hash);
    Hash = NewHash;
}
void Escape(void *);
void Driver_14900(TMapFString *M, const TCHAR *K, const TCHAR *V) { Escape(&GMalloc); M->Add(K, V); }
void Driver_14980(TPairArray *A, TPairArray *B, INT I) { Escape(&GMalloc); A->~TPairArray(); B->Remove(I, 1); B->Remove(I + 1, 2); B->Remove(I, I); }
void Driver_149f0(TPairArray *A, TPairArray *B, INT Slack) { A->Empty(Slack); B->Empty(0); A->Empty(Slack); B->Empty(Slack + 1); A->Empty(2); }
