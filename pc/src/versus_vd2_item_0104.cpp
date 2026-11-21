// Work item 0104: Versus RVA 0x18620-0x18683.
// TMapBase destructor for a string map (TMap<FString,FString>-style layout:
// Pairs TArray at +0, Hash at +0xc, HashCount at +0x10). LTCG: this on the
// stack, ret 4. The Pairs array destructor (retail 0x1afb4d0, also LTCG with
// this on the stack) is called out of line.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

inline void appFree(void *Original) { GMalloc->Free(Original); }

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    ~FArray();
    void Remove(INT Index, INT Count, INT ElementSize);
};

class FString : public FArray
{
};

struct TPair
{
    INT HashNext;
    FString Key;
    FString Value;
};

// TArray<TPair>: its destructor destroys the pairs then frees the array.
class TPairArray : public FArray
{
public:
    ~TPairArray();
};

class FStringMap
{
public:
    TPairArray Pairs;
    INT *Hash;
    INT HashCount;

    ~FStringMap();
};

// RVA 0x18620
FStringMap::~FStringMap()
{
    if (Hash)
        appFree(Hash);
    Hash = 0;
    HashCount = 0;
}

// Scaffolding for the link, not part of the unit: retail 0x1afb4d0
// (TArray<TPair>::~TArray) defined here, unverified, only so the LTCG
// linker gives it its retail convention (this on the stack, ret 4).
TPairArray::~TPairArray()
{
    for (INT i = 0; i < ArrayNum; i++) {
        ((TPair *)Data)[i].Key.~FString();
        ((TPair *)Data)[i].Value.~FString();
    }
    Remove(0, ArrayNum, sizeof(TPair));
}
void Escape(void *);
void Driver_18620(FStringMap *M) { Escape(&GMalloc); M->~FStringMap(); }
