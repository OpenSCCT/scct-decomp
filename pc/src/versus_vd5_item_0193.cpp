// Work item 0193: Versus RVA 0xe30b0 and 0xe3130.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

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

// Releases a member's storage (retail 0xa7bf30).
void __stdcall ReleaseMember(void *member);

// Parent class whose destructor is at RVA 0x15ee0; name not recovered.
class UnnamedParent_15ee0 : public UObject { public: virtual ~UnnamedParent_15ee0(); };

// Class name not recovered (vtable at 0x10c044c0).
class UnnamedClass_e30b0 : public UnnamedParent_15ee0 {
public:
    struct Member { ~Member() { ReleaseMember(this); } };  // released through a helper
    virtual ~UnnamedClass_e30b0();
    InheritedData<0x2c - sizeof(UnnamedParent_15ee0)> ParentData;
    Member Field2C;
};
UnnamedClass_e30b0::~UnnamedClass_e30b0() { ConditionalDestroy(); }
