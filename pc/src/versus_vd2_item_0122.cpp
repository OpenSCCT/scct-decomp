// Work item 0122: Versus RVA 0x1fa70.
// TMapBase<FString,INT>::Add from UE2 Core (UnTemplate.h). A pair is 0x14
// bytes: HashNext, FString Key, a 4-byte value (INT used here; the value type
// is not pinned down by this function). LTCG object: the linker gave the
// members register calling conventions (this in EDI for Add, ESI for Rehash
// and the TPair constructor).

typedef unsigned short TCHAR;
typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

#define INDEX_NONE -1

extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const TCHAR *, const TCHAR *);

extern const TCHAR EmptyString[]; // 0x10c10928, TEXT("")

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

inline void *operator new(unsigned int, void *Mem) { return Mem; }

extern DWORD GCRCTable[256];

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
    INT Num() const { return ArrayNum; }
    INT Add(INT Count, INT ElementSize); // RVA 0x44e0
};

template <class T> class TArray : public FArray
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
};

class FString : public TArray<TCHAR>
{
public:
    FString(const TCHAR *In); // RVA 0x46c0
    ~FString();               // RVA 0x48b0
    const TCHAR *operator*() const { return ArrayNum ? (const TCHAR *)Data : EmptyString; }
    UBOOL operator==(const TCHAR *Other) const { return _wcsicmp(**this, Other) == 0; }
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
        // RVA 0x1faf0
        TPair(const TCHAR *InKey, const TI &InValue)
            : Key(InKey), Value(InValue)
        {
        }
    };

    TArray<TPair> Pairs;
    INT *Hash;
    INT HashCount;

    // RVA 0x1f9c0
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
    // RVA 0x1fa70
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
    // RVA 0x1f620
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
};

template class TMapBase<FString, INT>;

// Scaffolding for the link, not part of the unit. Retail Set (0x1f620) has
// three callers.
void Escape(void *);
void Driver_1fa70(TMapBase<FString, INT> *M, TMapBase<FString, INT> *N, const TCHAR *K, const INT *V, INT W)
{
    Escape(&GMalloc);
    Escape(&M->Set(K, *V));
    Escape(&N->Set(L"x", W));
    Escape(&M->Set(*V ? K : L"", W));
}
