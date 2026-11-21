// Work item 0286: Versus RVA 0xff140-0xff2c0.
// Neutral names: the class is named after its primary vtable (0x10c03dd0 is
// image-relative 0x303dd0); member element types are named after the
// destructor RVA retail passes to `eh_vector_destructor_iterator'.
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
    unsigned Reserved2[2];
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

class UnnamedClass30D7D8 : public UObject { public: virtual ~UnnamedClass30D7D8(); };

// Secondary interface base at +0x28 (vtable 0x10c03e60); no destructor.
class UnnamedInterface303E60 { public: virtual void InterfaceSlot0(); };

struct UnnamedElem1A3370 { char Pad[16]; ~UnnamedElem1A3370(); };
struct UnnamedElem279000 { char Pad[12]; ~UnnamedElem279000(); };
struct UnnamedElem11EF20 { char Pad[12]; ~UnnamedElem11EF20(); };

class UnnamedClass303DD0 : public UnnamedClass30D7D8, public UnnamedInterface303E60 {
public:
    virtual ~UnnamedClass303DD0();
    UnnamedElem1A3370 Slots[20];        // +0x2c
    UnnamedElem279000 Entries[255];     // +0x16c
    char Unknown_D60[0x114];
    UnnamedElem11EF20 Names[255];       // +0xe74
    UnnamedElem11EF20 ExtraNames[20];   // +0x1a68
};

UnnamedClass303DD0::~UnnamedClass303DD0()
{
    ConditionalDestroy();
}

// FMemCache::Get at 0xff220 (LTCG: Alignment in EAX, Item in EBX, ret 8).
typedef unsigned char BYTE;
typedef unsigned short _WORD;
typedef unsigned long DWORD;
typedef int INT;
typedef unsigned __int64 QWORD;
enum { COST_INFINITE = 0x1000000, HASH_COUNT = 16384 };

template <class T> inline T Align(const T Ptr, INT Alignment)
{
    return (T)(((DWORD)Ptr + Alignment - 1) & ~(Alignment - 1));
}

class FMemCache {
public:
    class FCacheItem {
    public:
        QWORD Id;
        BYTE *Data;
        _WORD Time;
        BYTE Segment;
        BYTE Extra;
        INT Cost;
        FCacheItem *LinearNext;
        FCacheItem *LinearPrev;
        FCacheItem *HashNext;
    };
    INT Initialized;
    _WORD Time;
    QWORD MruId;
    FCacheItem *MruItem;
    DWORD Unknown14[4];
    FCacheItem *HashItems[HASH_COUNT];

    static DWORD GHash(DWORD Val) { return (Val ^ (Val >> 12) ^ (Val >> 24)) & (HASH_COUNT - 1); }
    BYTE *Get(QWORD Id, FCacheItem *&Item, INT Alignment);
};

BYTE *FMemCache::Get(QWORD Id, FCacheItem *&Item, INT Alignment)
{
    if (Id == MruId) {
        Item = MruItem;
        MruItem->Cost += COST_INFINITE;
        return Align(MruItem->Data, Alignment);
    }
    for (FCacheItem *HashItem = HashItems[GHash((DWORD)Id)]; HashItem; HashItem = HashItem->HashNext) {
        if (HashItem->Id == Id) {
            MruId = Id;
            MruItem = HashItem;
            Item = HashItem;
            HashItem->Time = Time;
            HashItem->Cost += COST_INFINITE;
            return Align(HashItem->Data, Alignment);
        }
    }
    return 0;
}

// Scaffolding for the link, not part of the unit.
BYTE *Driver_ff220(FMemCache *Cache, QWORD Id, FMemCache::FCacheItem *&Item, INT Alignment)
{
    return Cache->Get(Id, Item, Alignment);
}
