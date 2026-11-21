// UActorChannel destructor (RVA 0xe1c90) from the Steam Versus payload. The
// deleting destructor at 0xe1c60 (UActorChannel) calls this. Its parent is the
// channel class matched as UnnamedClass304548 (0xe1de0, likely UChannel).
// Only the members this destructor touches are declared.
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

template<class T> class TArray {
public:
    ~TArray();
    T *Data;
    int ArrayNum;
    int ArrayMax;
};

// Releases a member's storage (0xaeecc0).
void __stdcall ReleaseMember(void *member);

class UnnamedClass304548 : public UObject { public: virtual ~UnnamedClass304548(); };

class UActorChannel : public UnnamedClass304548 {
public:
    struct Member { ~Member() { ReleaseMember(this); } };  // released through a helper
    virtual ~UActorChannel();
    InheritedData<0x80 - sizeof(UObject)> ChannelData;
    TArray<UObject *> Field80;
    TArray<unsigned char> Field8C;
    Member Field98;
};
UActorChannel::~UActorChannel() { ConditionalDestroy(); }
