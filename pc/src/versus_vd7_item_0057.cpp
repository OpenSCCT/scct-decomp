// Work item 0057: Versus RVA 0x134550-0x1347fe (FStatGraph methods).
// Names of FStatGraph, FStatGraphLine, and their members follow UE2 FStatGraph
// conventions (assumed from layout and behavior; no retail symbols for this class).
// Every function in this item was compiled with VC7.0 /GL and linked with /LTCG.

typedef unsigned short TCHAR;
typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

extern "C" __declspec(dllimport) INT __cdecl _wcsicmp(const TCHAR *, const TCHAR *);
extern "C" __declspec(dllimport) INT __cdecl _wcsnicmp(const TCHAR *, const TCHAR *, unsigned int);
extern "C" __declspec(dllimport) unsigned int __cdecl wcslen(const TCHAR *);
extern "C" __declspec(dllimport) TCHAR __cdecl towupper(TCHAR);

inline INT appStricmp(const TCHAR *A, const TCHAR *B) { return _wcsicmp(A, B); }
inline INT appStrnicmp(const TCHAR *A, const TCHAR *B, INT Count) { return _wcsnicmp(A, B, Count); }
inline INT appStrlen(const TCHAR *S) { return (INT)wcslen(S); }

extern DWORD GCRCTable[256];

// 0x1090f6b0: outside this item, defined so the link gives it its retail
// convention (Data in EAX).
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
    ~FArray()
    {
        if (Data)
        {
            GMalloc->Free(Data);
            Data = 0;
        }
        ArrayNum = ArrayMax = 0;
    }
    INT Add(INT Count, INT ElementSize);                    // 0x109044e0
    // 0x10915400 (LTCG: all args + this on stack)
    INT __stdcall AddZeroed(INT ElementSize, INT Count = 1);
    void Remove(INT Index, INT Count, INT ElementSize);     // 0x109119c0
};

template <class T> class TArray : public FArray
{
public:
    TArray() {}
    ~TArray();
    T &operator()(INT i) { return ((T *)Data)[i]; }
    const T &operator()(INT i) const { return ((T *)Data)[i]; }
    INT Num() const { return ArrayNum; }
    INT AddZeroed(INT Count = 1) { return FArray::AddZeroed(sizeof(T), Count); }
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

class FString : public FArray
{
public:
    FString() {}
    FString(const FString &Other);                  // 0x10904640
    FString(const TCHAR *In);                       // elsewhere
    ~FString();                                     // 0x109048b0
    FString &operator=(const FString &Other);       // 0x10904800
    const TCHAR *operator*() const { return ArrayNum ? (const TCHAR *)Data : L""; }
    UBOOL operator==(const TCHAR *Other) const { return appStricmp(**this, Other) == 0; }
    UBOOL operator==(const FString &Other) const { return appStricmp(**this, *Other) == 0; }
};

// Explicit specialization so ~TArray<FString>() stays out of line (0x1091ef20, thiscall).
template <> class TArray<FString> : public FArray
{
public:
    TArray() {}
    ~TArray();
    FString &operator()(INT i) { return ((FString *)Data)[i]; }
    const FString &operator()(INT i) const { return ((FString *)Data)[i]; }
    INT Num() const { return ArrayNum; }
};

template <class T> __declspec(noinline) TArray<T>::~TArray()
{
    Remove(0, ArrayNum);
}

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
        __declspec(noinline) ~TPair() {}
    };

    TArray<TPair> Pairs;
    INT *Hash;
    INT HashCount;

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

    __declspec(noinline) TMapBase() : Hash(0), HashCount(8) { Rehash(); }
    __declspec(noinline) ~TMapBase()
    {
        if (Hash)
            GMalloc->Free(Hash);
        Hash = 0;
        HashCount = 0;
    }

    __declspec(noinline) TI &Set(const TCHAR *InKey, const TI &InValue)
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
};

template <class TK, class TI> class TMap : public TMapBase<TK, TI>
{
};

struct FColor
{
    BYTE B, G, R, A;
};

struct FStatGraphLine
{
    UBOOL bHideLine;                // +0x00
    TArray<FLOAT> DataHistory;      // +0x04
    INT WritePos;                   // +0x10
    FColor LineColor;               // +0x14
    FString LineName;               // +0x18
    FLOAT YRange[2];                // +0x24
    FLOAT AutoScale;                // +0x2c
    UBOOL bAutoScale;               // +0x30
};

class FStatGraph
{
public:
    UBOOL bHideGraph;                       // +0x00
    UBOOL bLockScale;                       // +0x04
    TMap<FString, DWORD> LineNameMap;       // +0x08
    TArray<FStatGraphLine> Lines;           // +0x1c
    TArray<FString> Filter;                 // +0x28
    FLOAT XSize;                            // +0x34
    FLOAT YSize;                            // +0x38
    FLOAT XPos;                             // +0x3c
    FLOAT YPos;                             // +0x40
    INT GraphSize;                          // +0x44
    INT Field48;                            // +0x48
    FLOAT ZeroYRatio;                       // +0x4c
    BYTE BackgroundAlpha;                   // +0x50
    FString FilterString;                   // +0x54

    __declspec(noinline) FStatGraph();
    __declspec(noinline) ~FStatGraph();
    __declspec(noinline) UBOOL CheckFilter(const TCHAR *Name);
    __declspec(noinline) const TCHAR *GetFilterValue(const TCHAR *Prefix, const TCHAR *Default);
    __declspec(noinline) void AddLine(FString LineName, FColor Color,
                                      FLOAT YRangeMin, FLOAT YRangeMax);
};

// RVA 0x134550
UBOOL FStatGraph::CheckFilter(const TCHAR *Name)
{
    for (INT i = 0; i < Filter.Num(); i++)
    {
        if (appStricmp(*Filter(i), Name) == 0)
            return 1;
    }
    return 0;
}

// RVA 0x1345b0
const TCHAR *FStatGraph::GetFilterValue(const TCHAR *Prefix, const TCHAR *Default)
{
    for (INT i = 0; i < Filter.Num(); i++)
    {
        if (appStrnicmp(*Filter(i), Prefix, appStrlen(Prefix)) == 0)
            return *Filter(i) + appStrlen(Prefix);
    }
    return Default;
}

// RVA 0x134640
FStatGraph::FStatGraph()
{
    bHideGraph = 1;
    bLockScale = 0;
    XSize = 250.0f;
    YSize = 150.0f;
    XPos = 100.0f;
    YPos = 200.0f;
    GraphSize = 100;
    Field48 = 0;
    ZeroYRatio = 0.33f;
    BackgroundAlpha = 100;
}

// RVA 0x1346b0
FStatGraph::~FStatGraph()
{
}

// RVA 0x134720
void FStatGraph::AddLine(FString LineName, FColor Color, FLOAT YRangeMin, FLOAT YRangeMax)
{
    FStatGraphLine *Line = new (Lines) FStatGraphLine;
    Line->bHideLine = 0;
    Line->DataHistory.AddZeroed(256);
    Line->WritePos = 0;
    Line->LineColor = Color;
    Line->LineName = LineName;
    Line->YRange[0] = YRangeMin;
    Line->YRange[1] = YRangeMax;
    Line->AutoScale = 0.2f;
    Line->bAutoScale = 0;
    LineNameMap.Set(*Line->LineName, Lines.Num() - 1);
}

// ---- Scaffolding for the link, not part of the unit ----
void Escape(void *);
UBOOL Driver_134550(FStatGraph *G, const TCHAR *Name)
{
    return G->CheckFilter(Name);
}
const TCHAR *Driver_1345b0(FStatGraph *G, const TCHAR *Prefix, const TCHAR *Default)
{
    return G->GetFilterValue(Prefix, Default);
}
FStatGraph *Driver_134640(void *Mem)
{
    Escape(&GMalloc);
    return new (Mem) FStatGraph;
}
void Driver_1346b0(FStatGraph *G)
{
    Escape(&GMalloc);
    G->~FStatGraph();
}
void Driver_134720(FStatGraph *G, FString Name, FColor Color, FLOAT Min, FLOAT Max)
{
    Escape(&GMalloc);
    G->AddLine(Name, Color, Min, Max);
}
