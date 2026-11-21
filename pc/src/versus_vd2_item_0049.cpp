// Versus RVA 0xcd20: destructor of an Unreal Engine 2 class whose vtable is at
// image-base-relative 0x30d2f8 (named UnnamedClass30D2F8 since no registered
// constructor identifies it). Its parent is UnnamedClass30D6A0 (destructor at
// RVA 0xcc80); it owns one member at 0x3c with an out-of-line destructor
// (RVA 0xf2c0). Like every DECLARE_CLASS destructor it first runs
// UObject::ConditionalDestroy().
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

template<unsigned Size> struct InheritedData { unsigned char Bytes[Size]; };

class UnnamedClass30D6A0 : public UObject { public: virtual ~UnnamedClass30D6A0(); };

// Member at 0x3c; its destructor (RVA 0xf2c0) is matched elsewhere or open.
struct UnnamedMember0F2C0 { ~UnnamedMember0F2C0(); };

class UnnamedClass30D2F8 : public UnnamedClass30D6A0 {
public:
    virtual ~UnnamedClass30D2F8();
    InheritedData<0x3c - sizeof(UnnamedClass30D6A0)> ParentData;
    UnnamedMember0F2C0 Field3C;
};
UnnamedClass30D2F8::~UnnamedClass30D2F8() { ConditionalDestroy(); }
