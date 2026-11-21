// Destructor at RVA 0xf4af0 of a material class deriving from UnnamedClass309E00
// (vtable 0x10c03f10, so named UnnamedClass303F10 after its vtable relative to the
// image base). It runs UObject::ConditionalDestroy(), destroys a member at +0x70
// through a stdcall helper (FUN_109f4d30), then runs the parent destructor.
enum { INDEX_NONE = -1 };
enum EObjectFlags { RF_Destroyed = 0x00800000, RF_DebugDestroy = 0x80000000 };

template<unsigned Size> struct InheritedData { unsigned char Bytes[Size]; };

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

class UnnamedClass309E00 : public UObject { public: virtual ~UnnamedClass309E00(); };

// Releases the member's storage (FUN_109f4d30).
void __stdcall ReleaseMember(void *member);

class UnnamedClass303F10 : public UnnamedClass309E00 {
public:
    struct Member { ~Member() { ReleaseMember(this); } };
    virtual ~UnnamedClass303F10();
    InheritedData<0x70 - sizeof(UObject)> ParentData;
    Member Field70;
};
UnnamedClass303F10::~UnnamedClass303F10() { ConditionalDestroy(); }
