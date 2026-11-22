// Work item 0094: Versus RVA 0xad440, AHUD::~AHUD.
// Placed directly after @delete_AHUD@8 (0xad410), whose deleting destructor
// calls it; the class derives from AActor. Member names are neutral: an
// array of 8 records (0x1c bytes each, destructor at 0xa79000) at 0x2fc and
// an FString at 0x40c.
#include "versus_build.h"
#include "unreal_containers.h"
typedef unsigned short TCHAR;
typedef int INT;

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
    INT Index;
    unsigned Reserved[5];
    unsigned ObjectFlags;
    INT ConditionalDestroy()
    {
        if (Index != INDEX_NONE && !(ObjectFlags & RF_Destroyed)) {
            ObjectFlags = (ObjectFlags & ~(RF_DebugDestroy | RF_Destroyed)) | RF_Destroyed;
            Destroy();
            return 1;
        }
        return 0;
    }
};

class AActor : public UObject {
public:
    virtual ~AActor();                    // 0x925d0
    unsigned char ActorData[0x2fc - 0x20];
};

struct FHUDRecord_1c {
    INT Fields[7];
    ~FHUDRecord_1c();                     // 0xa79000
};

class AHUD : public AActor {
public:
    virtual ~AHUD();
    FHUDRecord_1c Records[8];             // 0x2fc
    unsigned char Pad3dc[0x40c - 0x3dc];
    FString Text;                         // 0x40c
};

AHUD::~AHUD() { ConditionalDestroy(); }
