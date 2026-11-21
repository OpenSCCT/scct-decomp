// Work item 0081: TMap<FString,FConfigFile> helpers (Unreal Engine 2
// UnTemplate.h / FConfigCache.h), RVA 0x14520-0x14844.
// Pair layout (0x30 bytes): HashNext, FString Key, FConfigFile Value.
// FConfigFile is TMap<FString,FConfigSection> (0x14) + Dirty, NoSave, Quotes.
// Map layout: TArray<TPair> Pairs (+0), INT* Hash (+0xc), INT HashCount (+0x10).
// These functions come from an LTCG object (custom calling conventions).

typedef unsigned short TCHAR;
typedef unsigned char BYTE;
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

extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const TCHAR *, const TCHAR *);
extern DWORD GCRCTable[256];
TCHAR appToUpper(TCHAR c);

// appStrihash (RVA 0xf6b0; defined so the link gives it its retail register
// convention: Data in EAX).
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
extern const TCHAR EmptyString[];   // L"" shared in retail

typedef char *va_list;
extern "C" __declspec(dllimport) int __cdecl _vsnwprintf(TCHAR *, unsigned int, const TCHAR *, va_list);

class FOutputDevice
{
public:
    virtual void Serialize(const TCHAR *V, INT Event) = 0;
    virtual void Flush();
    void Logf(const TCHAR *Fmt, ...);
};

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    FArray(INT InNum, INT ElementSize)
        : ArrayNum(InNum), ArrayMax(InNum)
    {
        Data = ArrayMax ? GMalloc->Malloc(ArrayMax * ElementSize, L"FArray") : 0;
    }
    ~FArray()
    {
        if (Data)
        {
            GMalloc->Free(Data);
            Data = 0;
        }
        ArrayNum = ArrayMax = 0;
    }
    INT Num() const { return ArrayNum; }
    INT Add(INT Count, INT ElementSize);
    void Empty(INT ElementSize, INT Slack);
    void Remove(INT Index, INT Count, INT ElementSize);
};

class FString : public FArray
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

// TArray<BYTE>
class TByteArray : public FArray
{
public:
    void Remove(INT Index, INT Count) { FArray::Remove(Index, Count, sizeof(BYTE)); }
    ~TByteArray() { Remove(0, ArrayNum); }
};

inline void *operator new(unsigned int, void *Mem) { return Mem; }

// TMap<FString,FConfigSection>: only what the assignment needs.
struct FSubPair    // TPair<FString,FString>
{
    INT HashNext;
    FString Key;
    FString Value;
    FSubPair(const FSubPair &Other);
    ~FSubPair();
};

class FSubPairArray : public FArray    // TArray<TPair<FString,FString> >
{
public:
    FSubPair &operator()(INT i) const { return ((FSubPair *)Data)[i]; }
    FSubPairArray(const FSubPairArray &Other);
    ~FSubPairArray();
};

// RVA 0x152b0 (defined for its register convention).
__declspec(noinline) FSubPairArray::FSubPairArray(const FSubPairArray &Other)
    : FArray(Other.ArrayNum, sizeof(FSubPair))
{
    ArrayNum = 0;
    for (INT i = 0; i < Other.ArrayNum; i++)
        new(&(*this)(FArray::Add(1, sizeof(FSubPair)))) FSubPair(Other(i));
}

class FConfigSection    // TMultiMap<FString,FString>
{
public:
    FSubPairArray Pairs;
    INT *Hash;
    INT HashCount;
    void Rehash();
    FConfigSection(const FConfigSection &Other);
    ~FConfigSection();
};

// RVA 0x150a0 (defined for its register convention).
__declspec(noinline) FConfigSection::FConfigSection(const FConfigSection &Other)
    : Pairs(Other.Pairs), Hash(0), HashCount(Other.HashCount)
{
    Rehash();
}

struct FSectionPair
{
    INT HashNext;
    FString Key;
    FConfigSection Value;
    // RVA 0x15250 (defined for its register convention: Other in EDI).
    FSectionPair(const FSectionPair &Other)
        : HashNext(Other.HashNext), Key(Other.Key), Value(Other.Value) {}
    ~FSectionPair() {}
};

class FSectionPairArray : public FArray
{
public:
    FSectionPairArray() {}
    FSectionPairArray(const FSectionPairArray &Other);
    FSectionPair &operator()(INT i) const { return ((FSectionPair *)Data)[i]; }
    void Empty(INT Slack);
    // TArray<TPair>::operator= (RVA 0x15190; defined for its register convention).
    FSectionPairArray &operator=(const FSectionPairArray &Other)
    {
        if (this != &Other)
        {
            Empty(Other.ArrayNum);
            for (INT i = 0; i < Other.ArrayNum; i++)
                new(&(*this)(FArray::Add(1, sizeof(FSectionPair)))) FSectionPair(Other(i));
        }
        return *this;
    }
    ~FSectionPairArray();
};

// TArray<TPair>::Empty (RVA 0x14bd0; defined for its register convention).
__declspec(noinline) void FSectionPairArray::Empty(INT Slack)
{
    for (INT i = 0; i < ArrayNum; i++)
        (&(*this)(i))->~FSectionPair();
    FArray::Empty(sizeof(FSectionPair), Slack);
}

class FConfigFile
{
public:
    FSectionPairArray Pairs;
    INT *Hash;
    INT HashCount;
    UBOOL Dirty;
    UBOOL NoSave;
    UBOOL Quotes;

    void Rehash();
    FConfigFile(const FConfigFile &Other)
        : Pairs(Other.Pairs), Hash(0), HashCount(Other.HashCount),
          Dirty(Other.Dirty), NoSave(Other.NoSave), Quotes(Other.Quotes)
    {
        Rehash();
    }
    ~FConfigFile()
    {
        if (Hash)
            GMalloc->Free(Hash);
        Hash = 0;
        HashCount = 0;
    }
    FConfigFile &operator=(const FConfigFile &Other)
    {
        Pairs = Other.Pairs;
        HashCount = Other.HashCount;
        Rehash();
        Dirty = Other.Dirty;
        NoSave = Other.NoSave;
        Quotes = Other.Quotes;
        return *this;
    }
};

struct TPair
{
    TPair(const TCHAR *InKey, const FConfigFile &InValue)
        : Key(InKey), Value(InValue) {}
    INT HashNext;
    FString Key;
    FConfigFile Value;
    ~TPair() {}
};

class TPairArray : public FArray
{
public:
    TPair &operator()(INT i) { return ((TPair *)Data)[i]; }
    void Remove(INT Index, INT Count = 1)
    {
        for (INT i = Index; i < Index + Count; i++)
            (&(*this)(i))->~TPair();
        FArray::Remove(Index, Count, sizeof(TPair));
    }
    ~TPairArray();
};

class TMapFConfigFile
{
public:
    TPairArray Pairs;
    INT *Hash;
    INT HashCount;

    TMapFConfigFile();
    void Rehash();
    void Relax()
    {
        while (HashCount > Pairs.Num() * 2 + 8)
            HashCount /= 2;
        Rehash();
    }
    FConfigFile &Add(const TCHAR *InKey, const FConfigFile &InValue);
    FConfigFile &Set(const TCHAR *InKey, const FConfigFile &InValue);
    INT Remove(const TCHAR *InKey);
    FConfigFile *Find(const FString &Key);
    void Dump(FOutputDevice &Ar);
};

// TMap<FString,FConfigFile>::Rehash (RVA 0x14c10; defined so the link gives
// it its retail register convention).
void TMapFConfigFile::Rehash()
{
    INT *NewHash = (INT *)GMalloc->Malloc(HashCount * sizeof(INT), L"HashMapHash");
    INT i;
    for (i = 0; i < HashCount; i++)
        NewHash[i] = -1;
    for (i = 0; i < Pairs.Num(); i++)
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

// TMap<FString,FConfigSection>::Rehash (RVA 0x14a30; defined for its
// register convention).
void FConfigFile::Rehash()
{
    INT *NewHash = (INT *)GMalloc->Malloc(HashCount * sizeof(INT), L"HashMapHash");
    INT i;
    for (i = 0; i < HashCount; i++)
        NewHash[i] = -1;
    for (i = 0; i < Pairs.Num(); i++)
    {
        FSectionPair &Pair = Pairs(i);
        INT iHash = GetTypeHash(Pair.Key) & (HashCount - 1);
        Pair.HashNext = NewHash[iHash];
        NewHash[iHash] = i;
    }
    if (Hash)
        GMalloc->Free(Hash);
    Hash = NewHash;
}

// TMap<FString,FConfigFile>::Add (RVA 0x14cc0; defined for its register
// convention).
__declspec(noinline) FConfigFile &TMapFConfigFile::Add(const TCHAR *InKey, const FConfigFile &InValue)
{
    TPair &Pair = *new(&Pairs(Pairs.FArray::Add(1, sizeof(TPair)))) TPair(InKey, InValue);
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

const TCHAR *appStrfind(const TCHAR *Str, const TCHAR *Find);
extern TCHAR GCmdLine[];                    // 0x10c92680
extern const TCHAR Logf_LogFlushParam[];    // 0x10c71070

// ParseParam (RVA 0x121c0; defined so the link gives it its retail register
// convention: Stream in EDI, Param in ESI).
UBOOL ParseParam(const TCHAR *Stream, const TCHAR *Param)
{
    const TCHAR *Start = Stream;
    if (*Stream)
    {
        while ((Start = appStrfind(Start + 1, Param)) != 0)
        {
            if (Start > Stream && (Start[-1] == '-' || Start[-1] == '/'))
                return 1;
        }
    }
    return 0;
}

// FOutputDevice::Logf (RVA 0x118d0; defined so the link gives it its retail
// register convention: this in EBX). The body is simplified.
void FOutputDevice::Logf(const TCHAR *Fmt, ...)
{
    TCHAR *Buffer = (TCHAR *)GMalloc->Malloc(0x10000, L"Logf");
    va_list ArgPtr = (va_list)&Fmt + sizeof(Fmt);
    _vsnwprintf(Buffer, 0x8000, Fmt, ArgPtr);
    Serialize(Buffer, 0x24c);
    GMalloc->Free(Buffer);
    if (!ParseParam(GCmdLine, Logf_LogFlushParam))
        Flush();
}

// RVA 0x14520: TMap<FString,FConfigFile>::TMap()
TMapFConfigFile::TMapFConfigFile()
    : Hash(0), HashCount(8)
{
    Rehash();
}

// RVA 0x14570: TMap<FString,FConfigFile>::Set
FConfigFile &TMapFConfigFile::Set(const TCHAR *InKey, const FConfigFile &InValue)
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

// RVA 0x14610: TMap<FString,FConfigFile>::Remove
INT TMapFConfigFile::Remove(const TCHAR *InKey)
{
    INT Count = 0;
    for (INT i = Pairs.Num() - 1; i >= 0; i--)
        if (Pairs(i).Key == InKey)
        {
            Pairs.Remove(i);
            Count++;
        }
    if (Count)
        Relax();
    return Count;
}

// RVA 0x146f0: TMap<FString,FConfigFile>::Find
FConfigFile *TMapFConfigFile::Find(const FString &Key)
{
    for (INT i = Hash[GetTypeHash(Key) & (HashCount - 1)]; i != -1; i = Pairs(i).HashNext)
        if (Pairs(i).Key == Key)
            return &Pairs(i).Value;
    return 0;
}

// RVA 0x14780: TMap<FString,FConfigFile>::Dump
void TMapFConfigFile::Dump(FOutputDevice &Ar)
{
    Ar.Logf(L"TMapBase: %i items, %i hash slots", Pairs.Num(), HashCount);
    for (INT i = 0; i < HashCount; i++)
    {
        INT c = 0;
        for (INT j = Hash[i]; j != -1; j = Pairs(j).HashNext)
            c++;
        Ar.Logf(L"   Hash[%i] = %i", i, c);
    }
}

// RVA 0x147e0: TArray<BYTE>::~TArray (out of line; defined in the class above)

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_14520(void *Mem) { Escape(new(Mem) TMapFConfigFile); }
void Driver_14570(TMapFConfigFile *M, const TCHAR *K, INT *Out)
{
    TCHAR Buf[16];
    char Local[sizeof(FConfigFile)];
    INT A = Out[0], B = Out[1], C = Out[2];
    Escape(Buf); Escape(Local);
    M->Set(Buf, *(FConfigFile *)Local);
    Out[3] = A; Out[4] = B; Out[5] = C;
    Escape(M);
}
void Driver_14610(TMapFConfigFile *M, const TCHAR *K) { Escape((void *)M->Remove(K)); }
void Driver_146f0(TMapFConfigFile *M, const FString *K) { Escape(M->Find(*K)); }
void Driver_14780(TMapFConfigFile *M, FOutputDevice *Ar) { M->Dump(*Ar); }
void Driver_147e0(TByteArray *A) { Escape(&GMalloc); A->~TByteArray(); }
void Driver_14cc0(TMapFConfigFile *M, const TCHAR *K, const FConfigFile *V) { Escape(&M->Add(K, *V)); }
