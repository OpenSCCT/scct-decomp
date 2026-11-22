// UConsole::~UConsole (RVA 0xab640) from the Steam Versus payload.
// The deleting destructor at 0xab610 is @delete_UConsole@8, so this is the class
// destructor: ConditionalDestroy(), then the members in reverse order, then
// UInteraction::~UInteraction. Member names are neutral; the two 16-entry arrays
// of 12-byte elements are destroyed through one shared out-of-line destructor
// (0xa79000), likely the console's history/scrollback string rings.
#include "versus_build.h"
#include "unreal_containers.h"
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

// 12-byte element with its own out-of-line destructor (0xa79000).
struct FConsoleLine {
    ~FConsoleLine();
    void *Data;
    int ArrayNum;
    int ArrayMax;
};

class UInteraction : public UObject {
public:
    virtual ~UInteraction();
    unsigned char UInteractionData[0x44 - 0x20];
};

class UConsole : public UInteraction {
public:
    virtual ~UConsole();
    FString Field44;
    FConsoleLine Lines50[16];
    unsigned char Data110[0xc];
    FConsoleLine Lines11C[16];
};

UConsole::~UConsole() { ConditionalDestroy(); }
