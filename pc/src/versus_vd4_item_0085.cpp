// Work item 0085: Versus RVA 0x14e00-0x14f36.
// TMap pair destructors and TArray<TMap<FString,FString>::TPair>::Remove.
// The object was built with /GL and linked with /LTCG: the destructors take
// `this` on the stack (ret 4) and Remove takes Index in EDI.
typedef unsigned short TCHAR;
typedef int INT;

class FMalloc
{
public:
    virtual void *Malloc(unsigned long Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, unsigned long Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    ~FArray()
    {
        if (Data)
            GMalloc->Free(Data);
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
    void Remove(INT Index, INT Count, INT ElementSize);   // RVA 0x119c0
};

class FString : public FArray
{
public:
    ~FString();                                          // RVA 0x48b0
};

// TMap<FString,FString>::TPair (0x1c bytes)
struct TPairStringString
{
    INT HashNext;
    FString Key;
    FString Value;
    ~TPairStringString();
};

// TArray<TMap<FString,FString>::TPair>
class TPairStringStringArray : public FArray
{
public:
    ~TPairStringStringArray();                           // RVA 0x14980
    void Remove(INT Index, INT Count);
};

// Pair array of the other nested map; its pair type is unknown.
class UnnamedPairArray_14b60 : public FArray
{
public:
    ~UnnamedPairArray_14b60();                           // RVA 0x14b60
};

// TMap<FString,FString> (TMapBase layout: Pairs, Hash, HashCount).
class TMapStringString
{
public:
    TPairStringStringArray Pairs;
    INT *Hash;
    INT HashCount;
    ~TMapStringString();                                 // RVA 0xab0d0
};

// Another nested TMap<FString,?> (neutral name).
class UnnamedMap_103a0
{
public:
    UnnamedPairArray_14b60 Pairs;
    INT *Hash;
    INT HashCount;
    ~UnnamedMap_103a0();                                 // RVA 0x103a0
};

// TMap<FString,TMap<FString,FString>>::TPair
struct TPairStringMap
{
    INT HashNext;
    FString Key;
    TMapStringString Value;
    ~TPairStringMap();
};

// TMap<FString,UnnamedMap_103a0>::TPair
struct TPairStringUnnamedMap
{
    INT HashNext;
    FString Key;
    UnnamedMap_103a0 Value;
    ~TPairStringUnnamedMap();
};

// RVA 0x14e00
TPairStringString::~TPairStringString()
{
}

// RVA 0x14e50
TPairStringMap::~TPairStringMap()
{
}

// RVA 0x14ea0
TPairStringUnnamedMap::~TPairStringUnnamedMap()
{
}

// RVA 0x14ef0
void TPairStringStringArray::Remove(INT Index, INT Count)
{
    for (INT i = Index; i < Index + Count; i++)
        (&((TPairStringString *)Data)[i])->~TPairStringString();
    FArray::Remove(Index, Count, sizeof(TPairStringString));
}

// The callers below are defined so the LTCG link sees retail's call graph
// (and gives the functions above their retail conventions); they belong to
// neighbouring items.

// RVA 0x14980
TPairStringStringArray::~TPairStringStringArray()
{
    Remove(0, ArrayNum);
}

// RVA 0xab0d0
TMapStringString::~TMapStringString()
{
    if (Hash)
        GMalloc->Free(Hash);
    Hash = 0;
    HashCount = 0;
}

// RVA 0x103a0
UnnamedMap_103a0::~UnnamedMap_103a0()
{
    if (Hash)
        GMalloc->Free(Hash);
    Hash = 0;
    HashCount = 0;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_14e00(TPairStringString *P) { P->~TPairStringString(); }
void Driver_14e50(TPairStringMap *P) { P->~TPairStringMap(); }
void Driver_14ea0(TPairStringUnnamedMap *P) { P->~TPairStringUnnamedMap(); }
void Driver_14ef0(TPairStringMap *P) { Escape(&GMalloc); P->~TPairStringMap(); }
