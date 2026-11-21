// Work item 0084 (RVA 0x14cc0-0x14da4): TMap<FString,FConfigFile> internals
// from UE2 Core (UnTemplate.h / FConfigCache.h), compiled with /GL and linked
// with /LTCG (custom calling conventions).
//   0x14cc0  TMap<FString,FConfigFile>::Add (this in EAX, ret 8)
//   0x14d40  TArray<TMap<FString,FConfigFile>::TPair>::~TArray (this on stack, ret 4)

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

extern const TCHAR EmptyString[]; // 0x10c10928, TEXT("")
extern DWORD GCRCTable[256];      // 0x10c78cd0

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

inline TCHAR appToUpper(TCHAR c) { return (c < 'a' || c > 'z') ? c : (TCHAR)(c - ('a' - 'A')); }

// 0xf6b0, appStrihash (string in EAX under LTCG).
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
    INT Add(INT Count, INT ElementSize);                 // 0x44e0
    void Remove(INT Index, INT Count, INT ElementSize);  // 0x119c0
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

template <class T> class TArray : public FArray
{
public:
    ~TArray() { Remove(0, ArrayNum); }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    INT Num() const { return ArrayNum; }
    void Remove(INT Index, INT Count = 1);
};

// 0x14db0 (Index in EDI, this on stack under LTCG); not inlined in retail.
template <class T> __declspec(noinline) void TArray<T>::Remove(INT Index, INT Count)
{
    for (INT i = Index; i < Index + Count; i++)
        (&(*this)(i))->~T();
    FArray::Remove(Index, Count, sizeof(T));
}

template <class T> inline void *operator new(unsigned int Size, TArray<T> &Array)
{
    INT Index = Array.FArray::Add(1, Size);
    return &Array(Index);
}
inline void *operator new(unsigned int, void *Mem) { return Mem; }

class FString : public TArray<TCHAR>
{
public:
    FString(const FString &Other);                      // 0x46c0
    ~FString();
    const TCHAR *operator*() const { return ArrayNum ? (const TCHAR *)Data : EmptyString; }
};
inline DWORD GetTypeHash(const FString &S) { return appStrihash(*S); }

// TMap<FString,FConfigSection> base of FConfigFile; layout only.
class FConfigSectionMap
{
public:
    char Pad[0x14];
    FConfigSectionMap(const FConfigSectionMap &Other);  // 0x15140
    ~FConfigSectionMap();
};

class FConfigFile : public FConfigSectionMap
{
public:
    UBOOL Dirty;
    UBOOL NoSave;
    INT Extra;
};

template <class TK, class TI> class TMap
{
public:
    class TPair
    {
    public:
        INT HashNext;
        TK Key;
        TI Value;
        TPair(const TK &InKey, const TI &InValue) : Key(InKey), Value(InValue) {}
        ~TPair() {}
    };

    TArray<TPair> Pairs;
    INT *Hash;
    INT HashCount;

    // 0x14c10 (this in ESI under LTCG).
    void Rehash()
    {
        INT *NewHash = (INT *)GMalloc->Malloc(HashCount * sizeof(INT), L"HashMapHash");
        {
            for (INT i = 0; i < HashCount; i++)
                NewHash[i] = -1;
        }
        for (INT i = 0; i < Pairs.Num(); i++)
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

    // 0x14cc0
    TI &Add(const TK &InKey, const TI &InValue)
    {
        TPair &Pair = *new (Pairs) TPair(InKey, InValue);
        INT iHash = (GetTypeHash(Pair.Key) & (HashCount - 1));
        Pair.HashNext = Hash[iHash];
        Hash[iHash] = Pairs.Num() - 1;
        if (HashCount * 2 + 8 < Pairs.Num())
        {
            HashCount *= 2;
            Rehash();
        }
        return Pair.Value;
    }
};

typedef TMap<FString, FConfigFile> FConfigFileMap;

// Scaffolding for the link, not part of the unit.
void Escape(void *);
FConfigFile *Driver_14cc0(FConfigFileMap *Map, const FString &Key, const FConfigFile &Value)
{
    Escape(&GMalloc);
    return &Map->Add(Key, Value);
}
void Driver_14d40(TArray<FConfigFileMap::TPair> *Pairs)
{
    Escape(&GMalloc);
    Pairs->~TArray();
}
