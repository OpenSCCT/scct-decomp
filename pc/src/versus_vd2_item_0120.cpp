// Work item 0120 (RVA 0x1f5d0-0x1f846): UE2 UnTemplate.h code compiled with
// /GL and linked with /LTCG, so calling conventions are the linker's own:
//   0x1f5d0  TMap<FString,DWORD>::TMap()                 (this on stack, ret 4)
//   0x1f620  TMap<FString,DWORD>::Set(Key, Value)        (this in EAX, Key in EBX)
//   0x1f690  TMap<FString,DWORD>::Find(const FString&)   (this in EBX)
//   0x1f720  destructor of a 0x3c record of five FStrings (this on stack)
//   0x1f7b0  TArray<0x2c record>::Remove(Index, Count)   (Index in EDI)
//   0x1f800  TArray<0x3c record>::Remove(Index, Count)   (Index in EDI)
// The map value type is a 4-byte value of unknown meaning (DWORD here); the
// record types have neutral names.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

extern "C" __declspec(dllimport) INT __cdecl _wcsicmp(const TCHAR *, const TCHAR *);
extern DWORD GCRCTable[256];
extern "C" __declspec(dllimport) TCHAR __cdecl towupper(TCHAR);
// 0x1090f6b0: outside this item, defined so the link gives it its retail
// convention (string in EAX).
__declspec(noinline) DWORD appStrihash(const TCHAR *Data)
{
    DWORD Hash = 0;
    while (*Data)
    {
        TCHAR Ch = towupper(*Data++);
        unsigned char B = (unsigned char)Ch;
        Hash = ((Hash >> 8) & 0x00FFFFFF) ^ GCRCTable[(Hash ^ B) & 0x000000FF];
        B = (unsigned char)(Ch >> 8);
        Hash = ((Hash >> 8) & 0x00FFFFFF) ^ GCRCTable[(Hash ^ B) & 0x000000FF];
    }
    return Hash;
}
inline INT appStricmp(const TCHAR *A, const TCHAR *B) { return _wcsicmp(A, B); }

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
    void Remove(INT Index, INT Count, INT ElementSize);   // 0x109119c0
    INT Add(INT Count, INT ElementSize);                  // 0x109044e0
};

template <class T> class TArray : public FArray
{
public:
    TArray() {}
    ~TArray() { Remove(0, ArrayNum); }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    const T &operator()(INT i) const { return ((T *)Data)[i]; }
    INT Num() const { return ArrayNum; }
    __declspec(noinline) void Remove(INT Index, INT Count = 1)
    {
        for (INT i = Index; i < Index + Count; i++)
            (&(*this)(i))->~T();
        FArray::Remove(Index, Count, sizeof(T));
    }
};

inline void *operator new(unsigned int, void *Mem) { return Mem; }
template <class T> inline void *operator new(unsigned int Size, TArray<T> &Array)
{
    INT Index = Array.FArray::Add(1, Size);
    return &Array(Index);
}

class FString : public TArray<TCHAR>
{
public:
    FString(const TCHAR *In);                     // elsewhere
    ~FString();                                   // 0x109048b0
    const TCHAR *operator*() const { return ArrayNum ? (const TCHAR *)Data : L""; }
    UBOOL operator==(const TCHAR *Other) const { return appStricmp(**this, Other) == 0; }
    UBOOL operator==(const FString &Other) const { return appStricmp(**this, *Other) == 0; }
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
        TPair(const TCHAR *InKey, const TI &InValue) : Key(InKey), Value(InValue) {}
    };

    TArray<TPair> Pairs;
    INT *Hash;
    INT HashCount;

    // 0x1091f9c0 and 0x1091fa70: outside this item, defined here only so the
    // link gives them their retail conventions.
    __declspec(noinline) void Rehash()
    {
        INT *NewHash = (INT *)GMalloc->Malloc(HashCount * sizeof(INT), L"HashMapHash");
        for (INT i = 0; i < HashCount; i++)
            NewHash[i] = -1;
        for (INT i = 0; i < Pairs.Num(); i++)
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
    __declspec(noinline) TI &Add(const TCHAR *InKey, const TI &InValue)
    {
        TPair &Pair = *new (Pairs) TPair(InKey, InValue);
        INT iHash = GetTypeHash(Pair.Key) & (HashCount - 1);
        Pair.HashNext = Hash[iHash];
        Hash[iHash] = Pairs.Num() - 1;
        if (HashCount * 2 + 8 < Pairs.Num())
        {
            HashCount *= 2;
            Rehash();
        }
        return Pair.Value;
    }

    TMapBase() : Hash(0), HashCount(8) { Rehash(); }
    TI &Set(const TCHAR *InKey, const TI &InValue)
    {
        for (INT i = Hash[GetTypeHash(InKey) & (HashCount - 1)]; i != -1; )
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
    TI *Find(const TK &Key)
    {
        for (INT i = Hash[GetTypeHash(Key) & (HashCount - 1)]; i != -1; i = Pairs(i).HashNext)
            if (Pairs(i).Key == Key)
                return &Pairs(i).Value;
        return 0;
    }
};

template <class TK, class TI> class TMap : public TMapBase<TK, TI>
{
};

typedef TMap<FString, DWORD> FUnnamedMap_1f5d0;

// 0x2c record whose destructor is out of line at 0x10906200 (outside this
// item; defined so the link gives it its retail convention, this on stack).
struct UnnamedRecord_6200
{
    FString A, B, C;
    DWORD D, E;
    __declspec(noinline) ~UnnamedRecord_6200() {}
};

// RVA 0x1f720: 0x3c record of five strings (compiler-generated destructor).
struct UnnamedRecord_1f720
{
    FString A, B, C, D, E;
    __declspec(noinline) ~UnnamedRecord_1f720() {}
};

// Explicit instantiations of the template members retail emits out of line.
template void TArray<UnnamedRecord_6200>::Remove(INT, INT);
template void TArray<UnnamedRecord_1f720>::Remove(INT, INT);

// ---- Scaffolding for the link, not part of the unit ----
void Escape(void *);
FUnnamedMap_1f5d0 *Driver_1f5d0(void *Mem) { Escape(&GMalloc); return new (Mem) FUnnamedMap_1f5d0; }
void Driver_1f620(FUnnamedMap_1f5d0 *M, FString &K, DWORD V) { Escape(&GMalloc); M->Set(*K, V); Escape(&V); }
DWORD *Driver_1f690(FUnnamedMap_1f5d0 *M, const FString &K) { return M->Find(K); }
void Driver_1f720(UnnamedRecord_1f720 *R) { R->~UnnamedRecord_1f720(); }
void Driver_1f7b0(TArray<UnnamedRecord_6200> *A, INT I, INT N) { A->Remove(I, N); }
void Driver_1f800(TArray<UnnamedRecord_1f720> *A, INT I, INT N) { A->Remove(I, N); }
