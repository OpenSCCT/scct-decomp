// Work item 0083: Versus RVA 0xab4c0-0xab607.
// UConsole destructor (UConsole's deleting destructor follows at 0xab610) and the
// placement constructor callback plus constructor of a neighbouring class whose
// name is not recovered (vtable 0x10c07758, called UnnamedClass_ab590 here).
enum { INDEX_NONE = -1 };
enum EObjectFlags { RF_Destroyed = 0x00800000, RF_DebugDestroy = 0x80000000 };
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned int size_t_;

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

template<unsigned Size> struct InheritedData { unsigned char Bytes[Size]; };

class FString {
public:
    enum ENoInit { EC_NoInit };
    FString();
    FString(ENoInit) {}
    ~FString();
    TCHAR *Data;
    INT ArrayNum;
    INT ArrayMax;
};

// FString that its owner leaves uninitialised (Unreal's FStringNoInit).
class FStringNoInit : public FString {
public:
    FStringNoInit() : FString(EC_NoInit) {}
};

class UInteractions : public UObject { public: virtual ~UInteractions(); };
class UInteraction : public UInteractions { public: virtual ~UInteraction(); };

class UConsole : public UInteraction {
public:
    virtual ~UConsole();
    InheritedData<0x34 - sizeof(UInteraction)> UInteractionData;
    FString History[256];
};

UConsole::~UConsole() { ConditionalDestroy(); }

// Name not recovered; vtable at 0x10c07758.
// Parent class name not recovered either.
class UnnamedParent_ab590 : public UObject { public: virtual ~UnnamedParent_ab590(); };
class UnnamedClass_ab590 : public UnnamedParent_ab590 {
public:
    UnnamedClass_ab590();
    InheritedData<0x44 - sizeof(UnnamedParent_ab590)> ParentData;
    FStringNoInit Name44;
    FString FirstStrings[16];
    unsigned char Gap110[0x11c - 0x110];
    FString SecondStrings[16];
};

enum EInternal { EC_Internal };
inline void *operator new(unsigned int Size, EInternal *Mem) { return Mem; }
inline void operator delete(void *Object, EInternal *Mem) {}

UnnamedClass_ab590::UnnamedClass_ab590() {}

// UClass placement callback (DECLARE_CLASS InternalConstructor).
void InternalConstructor_UnnamedClass_ab590(void *X)
{
    new((EInternal *)X) UnnamedClass_ab590;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_ab550() { Escape((void *)&InternalConstructor_UnnamedClass_ab590); }
