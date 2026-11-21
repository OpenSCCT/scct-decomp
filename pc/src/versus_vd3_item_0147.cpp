// Item 0147: UPackageMap default constructor (RVA 0x3eb10), LTCG.
// Layout evidence: UObject base is 0x28 bytes; members are TArray (0x28),
// two TMaps (0x34, 0x48; their constructor at 0x4f670 sets HashCount = 8 and
// calls Rehash) and a TArray (0x5c), matching UE2 UPackageMap.
typedef int INT;
typedef unsigned long DWORD;

class UObject
{
public:
    UObject() {}
    virtual ~UObject();
    INT Index;
    UObject *HashNext;
    void *StateFrame;
    void *_Linker;
    INT _LinkerIndex;
    UObject *Outer;
    DWORD ObjectFlags;
    INT Name;
    void *Class;
};

class FArray
{
public:
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FArray();
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

template<class T> class TArray : public FArray
{
public:
    TArray() {}
};

class TMapBase
{
public:
    __declspec(noinline) TMapBase() : Hash(0), HashCount(8) { Rehash(); }
    ~TMapBase();
    void Rehash();
    INT Num() const { return Pairs.ArrayNum; }
    FArray Pairs;
    INT *Hash;
    INT HashCount;
};

void *appMalloc(DWORD Count, const unsigned short *Tag);
void appFree(void *Ptr);
extern const unsigned short HashMapHash_Tag[];

struct FMapPair { void *Key; INT Value; INT HashNext; };

// Out of line in retail at 0x5aca0 (called with this in ESI).
__declspec(noinline) void TMapBase::Rehash()
{
    INT *NewHash = (INT *)appMalloc(HashCount * sizeof(INT), HashMapHash_Tag);
    INT i;
    for (i = 0; i < HashCount; i++)
        NewHash[i] = -1;
    for (i = 0; i < Num(); i++) {
        FMapPair &Pair = ((FMapPair *)Pairs.Data)[i];
        INT iHash = (INT)(((DWORD)Pair.Key >> 4) & (HashCount - 1));
        Pair.HashNext = NewHash[iHash];
        NewHash[iHash] = i;
    }
    if (Hash)
        appFree(Hash);
    Hash = NewHash;
}

struct FPackageInfo;

class UPackageMap : public UObject
{
public:
    UPackageMap();
    TArray<FPackageInfo> List;
    TMapBase LinkerMap;
    TMapBase ClassFieldIndices;
    TArray<INT> NameIndices;
    INT MaxObjectIndex;
    INT MaxNameIndex;
};

UPackageMap::UPackageMap()
{
}

// Scaffolding for the link, not part of the unit.
inline void *operator new(unsigned int, void *Mem) { return Mem; }
void Escape(void *);
void Driver_3eb10(void *Mem, void *MapMem)
{
    Escape(new(Mem) UPackageMap);
    Escape(new(MapMem) TMapBase);
}
