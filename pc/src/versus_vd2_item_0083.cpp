// Work item 0083 (RVA 0x14ae0-0x14c08): TMap<FString,FConfigSection> helpers,
// the per-file section map of FConfigFile (UE2 Core FConfigCache.h).
// TPair is 0x24 bytes: HashNext, FString Key (+4), FConfigSection Value (+0x10,
// itself a TMultiMap<FString,FString>, 0x14 bytes).
// All three are LTCG code (this in EAX/ESI or on the stack).
//   0x14ae0 TMapBase<FString,FConfigSection>::Add
//   0x14b60 TArray<TPair>::~TArray
//   0x14bd0 TArray<TPair>::Empty

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

extern const TCHAR EmptyString[]; // 0x10c10928, TEXT("")

inline void *operator new(unsigned int, void *Mem) { return Mem; }

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

extern DWORD GCRCTable[256];
TCHAR appToUpper(TCHAR c);

// Core UnMisc.cpp; defined here so the link gives it its LTCG convention.
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

class FString
{
public:
    TCHAR *Data;
    INT ArrayNum;
    INT ArrayMax;
    FString(const FString &Other);
    ~FString();
    const TCHAR *operator*() const { return ArrayNum ? Data : EmptyString; }
};

inline DWORD GetTypeHash(const FString &S) { return appStrihash(*S); }

class FConfigSection
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT *Hash;
    INT HashCount;
    FConfigSection(const FConfigSection &Other);
    ~FConfigSection();
};

struct TPair
{
    INT HashNext;
    FString Key;
    FConfigSection Value;
    TPair(const FString &InKey, const FConfigSection &InValue);
    ~TPair();
};

template <class T> class TArray : public FArray
{
public:
    ~TArray() { Remove(0, ArrayNum); }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    void Remove(INT Index, INT Count);
    void Empty(INT Slack);
};

template <class T> void TArray<T>::Remove(INT Index, INT Count)
{
    for (INT i = Index; i < Index + Count; i++)
        (&(*this)(i))->~T();
    FArray::Remove(Index, Count, sizeof(T));
}

template <class T> void TArray<T>::Empty(INT Slack)
{
    for (INT i = 0; i < ArrayNum; i++)
        (&(*this)(i))->~T();
    FArray::Empty(sizeof(T), Slack);
}

template <class T> inline void *operator new(unsigned int Size, TArray<T> &Array)
{
    INT Index = Array.FArray::Add(1, Size);
    return &Array(Index);
}

class TMapBase
{
public:
    TArray<TPair> Pairs;
    INT *Hash;
    INT HashCount;

    void Rehash();
    FConfigSection &Add(const FString &InKey, const FConfigSection &InValue)
    {
        TPair &Pair = *new (Pairs) TPair(InKey, InValue);
        INT iHash = (GetTypeHash(Pair.Key) & (HashCount - 1));
        Pair.HashNext = Hash[iHash];
        Hash[iHash] = Pairs.ArrayNum - 1;
        if (HashCount * 2 + 8 < Pairs.ArrayNum)
        {
            HashCount *= 2;
            Rehash();
        }
        return Pair.Value;
    }
};

TPair::TPair(const FString &InKey, const FConfigSection &InValue)
    : Key(InKey), Value(InValue)
{
}

TPair::~TPair()
{
}

void TMapBase::Rehash()
{
    INT *NewHash = (INT *)GMalloc->Malloc(HashCount * sizeof(INT), L"HashMapHash");
    INT i;
    for (i = 0; i < HashCount; i++)
        NewHash[i] = -1;
    for (i = 0; i < Pairs.ArrayNum; i++)
    {
        TPair &Pair = Pairs(i);
        INT iHash = (GetTypeHash(Pair.Key) & (HashCount - 1));
        Pair.HashNext = NewHash[iHash];
        NewHash[iHash] = i;
    }
    if (Hash)
        GMalloc->Free(Hash);
    Hash = NewHash;
}

// Scaffolding for the link, not part of the unit (link with /O2 /Ob1 /Gy /GX).
void Escape(void *);
FConfigSection &Driver_14ae0(TMapBase *M, const FString &K, const FConfigSection &V) { return M->Add(K, V); }
void Driver_14b60(TArray<TPair> *A) { A->~TArray<TPair>(); }
void Driver_14bd0(TArray<TPair> *A, INT Slack) { Escape(&GMalloc); A->Empty(Slack); }
