// Work item 0086: Versus RVA 0x14f90-0x1518c.
// TMap pair constructors and copy helpers for the config cache maps
// (Unreal Engine 2 UnTemplate.h / FConfigCache.h), from an LTCG object
// (this on the stack, Other in ECX/EDI, TArray::operator= with this in EAX).
// Built with /O2 /Ob1 /Gy /GX: retail never inlines these out-of-line members.
//   0x14f90 TMap<FString,FString>::TPair::TPair(const TCHAR*, const TCHAR*)
//   0x14fe0 TMap<FString,FConfigSection>::TPair::TPair(const TCHAR*, const FConfigSection&)
//   0x15030 TMap<FString,FConfigFile>::TPair::TPair(const TCHAR*, const FConfigFile&)
//   0x150a0 TMapBase<FString,FString>::TMapBase(const TMapBase&)
//   0x150f0 TArray<TMap<FString,FString>::TPair>::operator=
//   0x15140 TMapBase<FString,FConfigSection>::TMapBase(const TMapBase&)

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

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    FArray(INT InNum, INT ElementSize)
        : ArrayNum(InNum), ArrayMax(InNum)
    {
        Data = ArrayMax ? GMalloc->Malloc(ArrayMax * ElementSize, L"FArray") : 0;
    }
    ~FArray()
    {
        if (Data)
            GMalloc->Free(Data);
        Data = 0;
        ArrayMax = ArrayNum = 0;
    }
    INT Add(INT Count, INT ElementSize);                 // RVA 0x44e0
    void Empty(INT ElementSize, INT Slack);              // RVA 0x4550
};

class FString : public FArray
{
public:
    FString(const TCHAR *In);                            // RVA 0x46c0
    FString(const FString &Other);                       // RVA 0x4640
    ~FString();                                          // RVA 0x48b0
    const TCHAR *operator*() const { return ArrayNum ? (const TCHAR *)Data : EmptyString; }
};
inline DWORD GetTypeHash(const FString &S) { return appStrihash(*S); }

// TMap<FString,FString>::TPair
struct TPairStringString
{
    INT HashNext;
    FString Key;
    FString Value;
    TPairStringString(const TCHAR *InKey, const TCHAR *InValue);
    TPairStringString(const TPairStringString &Other);   // RVA 0x151f0
    ~TPairStringString();                                // RVA 0x14e00
};

// TArray<TMap<FString,FString>::TPair>
class TPairStringStringArray : public FArray
{
public:
    TPairStringStringArray(const TPairStringStringArray &Other);   // RVA 0x152b0
    ~TPairStringStringArray();
    TPairStringString &operator()(INT i) const { return ((TPairStringString *)Data)[i]; }
    void Empty(INT Slack);                                         // RVA 0x149f0
    TPairStringStringArray &operator=(const TPairStringStringArray &Other);
};

inline void *operator new(unsigned int Size, TPairStringStringArray &Array)
{
    INT Index = Array.Add(1, Size);
    return &Array(Index);
}

// TMapBase<FString,FString>
class TMapBaseStringString
{
public:
    TPairStringStringArray Pairs;
    INT *Hash;
    INT HashCount;
    TMapBaseStringString(const TMapBaseStringString &Other);
    void Rehash();                                       // RVA 0x14850
};
// TMap<FString,FString>
class TMapStringString : public TMapBaseStringString
{
};
// TMultiMap<FString,FString>
class TMultiMapStringString : public TMapStringString
{
};
class FConfigSection : public TMultiMapStringString
{
};

// TMap<FString,FConfigSection>::TPair and its array
struct TPairStringSection
{
    INT HashNext;
    FString Key;
    FConfigSection Value;
    TPairStringSection(const TCHAR *InKey, const FConfigSection &InValue);
    TPairStringSection(const TPairStringSection &Other); // RVA 0x15250
    ~TPairStringSection();
};

class TPairStringSectionArray : public FArray
{
public:
    TPairStringSectionArray(const TPairStringSectionArray &Other); // RVA 0x15340
    ~TPairStringSectionArray();
    TPairStringSection &operator()(INT i) const { return ((TPairStringSection *)Data)[i]; }
};

inline void *operator new(unsigned int Size, TPairStringSectionArray &Array)
{
    INT Index = Array.Add(1, Size);
    return &Array(Index);
}

// TMapBase<FString,FConfigSection>
class TMapBaseStringSection
{
public:
    TPairStringSectionArray Pairs;
    INT *Hash;
    INT HashCount;
    TMapBaseStringSection(const TMapBaseStringSection &Other);
    void Rehash();                                       // RVA 0x14a30
};
// TMap<FString,FConfigSection>
class TMapStringSection : public TMapBaseStringSection
{
};

class FConfigFile : public TMapStringSection
{
public:
    UBOOL Dirty;
    UBOOL NoSave;
    UBOOL Quotes;
};

// TMap<FString,FConfigFile>::TPair
struct TPairStringFile
{
    INT HashNext;
    FString Key;
    FConfigFile Value;
    TPairStringFile(const TCHAR *InKey, const FConfigFile &InValue);
};

// RVA 0x14f90
TPairStringString::TPairStringString(const TCHAR *InKey, const TCHAR *InValue)
    : Key(InKey), Value(InValue)
{
}

// RVA 0x14fe0
TPairStringSection::TPairStringSection(const TCHAR *InKey, const FConfigSection &InValue)
    : Key(InKey), Value(InValue)
{
}

// RVA 0x15030
TPairStringFile::TPairStringFile(const TCHAR *InKey, const FConfigFile &InValue)
    : Key(InKey), Value(InValue)
{
}

// RVA 0x150a0
TMapBaseStringString::TMapBaseStringString(const TMapBaseStringString &Other)
    : Pairs(Other.Pairs), Hash(0), HashCount(Other.HashCount)
{
    Rehash();
}

// RVA 0x150f0
TPairStringStringArray &TPairStringStringArray::operator=(const TPairStringStringArray &Other)
{
    if (this != &Other)
    {
        Empty(Other.ArrayNum);
        for (INT i = 0; i < Other.ArrayNum; i++)
            new(*this) TPairStringString(Other(i));
    }
    return *this;
}

// RVA 0x15140
TMapBaseStringSection::TMapBaseStringSection(const TMapBaseStringSection &Other)
    : Pairs(Other.Pairs), Hash(0), HashCount(Other.HashCount)
{
    Rehash();
}

// Scaffolding for the link, not part of the unit: callees retail compiled into
// the same LTCG module, given bodies so the linker picks their conventions.
TPairStringString::TPairStringString(const TPairStringString &Other)
    : HashNext(Other.HashNext), Key(Other.Key), Value(Other.Value)
{
}
TPairStringSection::TPairStringSection(const TPairStringSection &Other)
    : HashNext(Other.HashNext), Key(Other.Key), Value(Other.Value)
{
}
TPairStringStringArray::TPairStringStringArray(const TPairStringStringArray &Other)
    : FArray(Other.ArrayNum, sizeof(TPairStringString))
{
    ArrayNum = 0;
    for (INT i = 0; i < Other.ArrayNum; i++)
        new(*this) TPairStringString(Other(i));
}
TPairStringSectionArray::TPairStringSectionArray(const TPairStringSectionArray &Other)
    : FArray(Other.ArrayNum, sizeof(TPairStringSection))
{
    ArrayNum = 0;
    for (INT i = 0; i < Other.ArrayNum; i++)
        new(*this) TPairStringSection(Other(i));
}
void TPairStringStringArray::Empty(INT Slack)
{
    for (INT i = 0; i < ArrayNum; i++)
        (&(*this)(i))->~TPairStringString();
    FArray::Empty(sizeof(TPairStringString), Slack);
}
void TMapBaseStringString::Rehash()
{
    INT *NewHash = (INT *)GMalloc->Malloc(HashCount * sizeof(INT), L"HashMapHash");
    INT i;
    for (i = 0; i < HashCount; i++)
        NewHash[i] = -1;
    for (i = 0; i < Pairs.ArrayNum; i++)
    {
        TPairStringString &Pair = Pairs(i);
        INT iHash = GetTypeHash(Pair.Key) & (HashCount - 1);
        Pair.HashNext = NewHash[iHash];
        NewHash[iHash] = i;
    }
    if (Hash)
        GMalloc->Free(Hash);
    Hash = NewHash;
}
void TMapBaseStringSection::Rehash()
{
    INT *NewHash = (INT *)GMalloc->Malloc(HashCount * sizeof(INT), L"HashMapHash");
    INT i;
    for (i = 0; i < HashCount; i++)
        NewHash[i] = -1;
    for (i = 0; i < Pairs.ArrayNum; i++)
    {
        TPairStringSection &Pair = Pairs(i);
        INT iHash = GetTypeHash(Pair.Key) & (HashCount - 1);
        Pair.HashNext = NewHash[iHash];
        NewHash[iHash] = i;
    }
    if (Hash)
        GMalloc->Free(Hash);
    Hash = NewHash;
}
void Escape(void *);
inline void *operator new(unsigned int, void *Mem) { return Mem; }
void Driver_14f90(void *Mem, const TCHAR *K, const TCHAR *V) { Escape(new(Mem) TPairStringString(K, V)); }
void Driver_14fe0(void *Mem, const TCHAR *K, const FConfigSection *V) { Escape(new(Mem) TPairStringSection(K, *V)); }
void Driver_15030(void *Mem, const TCHAR *K, const FConfigFile *V) { Escape(new(Mem) TPairStringFile(K, *V)); }
void Driver_150f0(TPairStringStringArray *A, const TPairStringStringArray *B) { Escape(&(*A = *B)); }
