// Work item 0146: UPackageMap destructor (RVA 0x3e9f0) and its class
// InternalConstructor (RVA 0x3eaa0).
// UPackageMapLevel's destructor calls 0x3e9f0 as its parent destructor, and the
// member layout (TArray at 0x28, two TMaps at 0x34 and 0x48, TArray at 0x5c)
// matches Unreal Engine 2's UPackageMap: List, LinkerMap, ClassFieldIndices,
// NameIndices.
enum { INDEX_NONE = -1 };
enum EObjectFlags { RF_Destroyed = 0x00800000, RF_DebugDestroy = 0x80000000 };

class UObject {
public:
    virtual ~UObject();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void Destroy();
    int Index;
    unsigned Reserved[5];
    unsigned ObjectFlags;
    unsigned Reserved20[2];
    int ConditionalDestroy()
    {
        if (Index != INDEX_NONE && !(ObjectFlags & RF_Destroyed)) {
            ObjectFlags = (ObjectFlags & ~(RF_DebugDestroy | RF_Destroyed)) | RF_Destroyed;
            Destroy();
            return 1;
        }
        return 0;
    }
};

// Out-of-line container teardown helpers the destructor calls.
struct FPackageInfo;
void __stdcall DestroyPackageInfoArray(void *Array);   // RVA 0x401b0
void __stdcall DestroyMap(void *Map);                  // RVA 0x5a1a0
void __stdcall ConstructMap(void *Map);                // RVA 0x4f670

struct TArrayPackageInfo {
    FPackageInfo *Data; int ArrayNum; int ArrayMax;
    TArrayPackageInfo() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~TArrayPackageInfo() { DestroyPackageInfoArray(this); }
};
struct TMapObjectInt {
    unsigned char Pairs[12]; void *Hash; int HashCount;
    TMapObjectInt() { ConstructMap(this); }
    ~TMapObjectInt() { DestroyMap(this); }
};
struct TMapObjectFieldCache {
    unsigned char Pairs[12]; void *Hash; int HashCount;
    TMapObjectFieldCache() { ConstructMap(this); }
    ~TMapObjectFieldCache() { DestroyMap(this); }
};
struct TArrayInt {
    int *Data; int ArrayNum; int ArrayMax;
    TArrayInt() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~TArrayInt();                                       // RVA 0x1ef20
};

class UPackageMap : public UObject {
public:
    TArrayPackageInfo List;
    TMapObjectInt LinkerMap;
    TMapObjectFieldCache ClassFieldIndices;
    TArrayInt NameIndices;
    virtual ~UPackageMap();
    UPackageMap();
    static void InternalConstructor(void *X);
};

UPackageMap::~UPackageMap() { ConditionalDestroy(); }

// RVA 0x3eb10; defined here so the LTCG link gives it retail's calling convention.
UPackageMap::UPackageMap() {}

enum EInternal { EC_Internal };
inline void *operator new(unsigned int, EInternal *Mem) { return Mem; }
inline void operator delete(void *, EInternal *) {}

void UPackageMap::InternalConstructor(void *X) { new((EInternal *)X) UPackageMap; }

// Scaffolding for the LTCG link, not part of the unit: the class registry takes
// InternalConstructor's address, so it keeps the ordinary cdecl convention.
void Escape(void *);
void Driver_3eaa0() { Escape((void *)&UPackageMap::InternalConstructor); }
