// Work item 0080: Versus RVA 0x14340-0x1450d.
// TMap<FString,FConfigSection> members from UE2 Core (UnTemplate.h), the map
// FConfigFile derives from (UnIni / FConfigCache.h). A pair is 0x24 bytes:
// HashNext, FString Key, FConfigSection Value (itself a
// TMultiMap<FString,FString>, pair 0x1c bytes). LTCG object: the linker gave
// these members register calling conventions (this in EBX/EAX/ESI).

typedef unsigned short TCHAR;
typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

#define INDEX_NONE -1

extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const TCHAR *, const TCHAR *);

extern const TCHAR EmptyString[]; // 0x10c10928, TEXT("")
extern DWORD GCRCTable[256];

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

inline void *operator new(unsigned int, void *Mem) { return Mem; }

inline TCHAR appToUpper(TCHAR c) { return (c < 'a' || c > 'z') ? c : (TCHAR)(c + 'A' - 'a'); }

// RVA 0xf6b0 (another unit; defined here so the link gives it its register convention).
DWORD appStrihash(const TCHAR *Data)
{
    DWORD Hash = 0;
    while (*Data)
    {
        TCHAR Ch = appToUpper(*Data++);
        BYTE B = (BYTE)Ch;
        Hash = ((Hash >> 8) & 0x00FFFFFF) ^ GCRCTable[(Hash ^ B) & 0x000000FF];
        B = (BYTE)(Ch >> 8);
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
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FArray();
    INT Num() const { return ArrayNum; }
    INT Add(INT Count, INT ElementSize);
    void Empty(INT ElementSize, INT Slack);
    void Shrink(INT ElementSize)
    {
        if (ArrayMax != ArrayNum)
        {
            ArrayMax = ArrayNum;
            Data = GMalloc->Realloc(Data, ArrayMax * ElementSize, L"FArray");
        }
    }
};

template <class T> class TArray : public FArray
{
public:
    TArray() {}
    TArray(const TArray &Other);
    T &operator()(INT i) { return ((T *)Data)[i]; }
    const T &operator()(INT i) const { return ((T *)Data)[i]; }
    void Shrink() { FArray::Shrink(sizeof(T)); }
    void Empty(INT Slack)
    {
        for (INT i = 0; i < ArrayNum; i++)
            (&(*this)(i))->~T();
        FArray::Empty(sizeof(T), Slack);
    }
    TArray &operator=(const TArray &Other)
    {
        if (this != &Other)
        {
            Empty(Other.ArrayNum);
            for (INT i = 0; i < Other.ArrayNum; i++)
                new ((T *)Data + FArray::Add(1, sizeof(T))) T(Other(i));
        }
        return *this;
    }
};

class FString : public TArray<TCHAR>
{
public:
    FString(const TCHAR *In);
    FString(const FString &Other);
    const TCHAR *operator*() const { return ArrayNum ? (const TCHAR *)Data : EmptyString; }
    UBOOL operator==(const TCHAR *Other) const { return _wcsicmp(**this, Other) == 0; }
    UBOOL operator==(const FString &Other) const { return _wcsicmp(**this, *Other) == 0; }
};

inline DWORD GetTypeHash(const TCHAR *S) { return appStrihash(S); }
inline DWORD GetTypeHash(const FString &S) { return appStrihash(*S); }

template <class TK, class TI> class TMapBase
{
public:
    class TPair
    {
    public:
        INT HashNext;
        TK Key;
        TI Value;
        TPair(const TCHAR *InKey, const TI &InValue)
            : Key(InKey), Value(InValue)
        {
        }
        TPair(const TPair &Other)
            : HashNext(Other.HashNext), Key(Other.Key), Value(Other.Value)
        {
        }
    };

    TArray<TPair> Pairs;
    INT *Hash;
    INT HashCount;

    void Rehash()
    {
        INT *NewHash = (INT *)GMalloc->Malloc(HashCount * sizeof(INT), L"HashMapHash");
        for (INT i = 0; i < HashCount; i++)
            NewHash[i] = INDEX_NONE;
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
    TI &Add(const TCHAR *InKey, const TI &InValue)
    {
        TPair &Pair = *new ((TPair *)Pairs.Data + Pairs.FArray::Add(1, sizeof(TPair))) TPair(InKey, InValue);
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

public:
    TMapBase()
        : Hash(0), HashCount(8)
    {
        Rehash();
    }
    ~TMapBase();
    TMapBase(const TMapBase &Other)
        : Pairs(Other.Pairs), Hash(0), HashCount(Other.HashCount)
    {
        Rehash();
    }
    TMapBase &operator=(const TMapBase &Other)
    {
        Pairs = Other.Pairs;
        HashCount = Other.HashCount;
        Rehash();
        return *this;
    }
    TI &Set(const TCHAR *InKey, const TI &InValue)
    {
        for (INT i = Hash[(GetTypeHash(InKey) & (HashCount - 1))]; i != INDEX_NONE;)
        {
            TPair &Pair = Pairs(i);
            if (Pair.Key == InKey)
            {
                Pair.Value = InValue;
                return Pair.Value;
            }
            i = Pair.HashNext;
        }
        return Add(InKey, InValue);
    }
    void Shrink()
    {
        Pairs.Shrink();
        while (HashCount > Pairs.Num() * 2 + 8)
            HashCount /= 2;
        Rehash();
    }
    TI *Find(const TK &Key)
    {
        for (INT i = Hash[(GetTypeHash(Key) & (HashCount - 1))]; i != INDEX_NONE; i = Pairs(i).HashNext)
            if (Pairs(i).Key == Key)
                return &Pairs(i).Value;
        return 0;
    }
};

template <class TK, class TI> class TMultiMap : public TMapBase<TK, TI>
{
};

template <class TK, class TI> class TMap : public TMapBase<TK, TI>
{
};

class FConfigSection : public TMultiMap<FString, FString>
{
};

typedef TMap<FString, FConfigSection> FConfigSectionMap;

// RVA 0x14340: TMapBase<FString,FConfigSection>::TMapBase()
// RVA 0x14390: TMapBase<FString,FConfigSection>::Shrink()
// RVA 0x143f0: TMapBase<FString,FConfigSection>::Set() (near: LTCG register choice differs)
// RVA 0x14480: TMapBase<FString,FConfigSection>::Find()
template class TMapBase<FString, FConfigSection>;

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_14340(void *Mem) { Escape(new (Mem) FConfigSectionMap); }
void Driver_14390(FConfigSectionMap *M) { Escape(&GMalloc); M->Shrink(); }
FConfigSection *Driver_143f0(FConfigSectionMap *File, const TCHAR *Section)
{
    FConfigSection *Sec = File->Find(FString(Section));
    if (!Sec)
        Sec = &File->Set(Section, FConfigSection());
    return Sec;
}
void Driver_14480(FConfigSectionMap *M, const FString *K) { Escape(M->Find(*K)); }
