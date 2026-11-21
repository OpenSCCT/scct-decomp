// Destructor of UEMFChannelTextures (vtable 0x10c088d0; its placement constructor
// and deleting destructor sit next to this function at 0xa9420/0xa9450).
// Runs UObject::ConditionalDestroy(), destroys the member array at +0x4C, then
// the parent's destructor (UnnamedClass30B990 at 0x99450).
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

class UnnamedClass30B990 : public UObject { public: virtual ~UnnamedClass30B990(); };

// Member array at +0x4C. Its out-of-line destruction routine (0xa7bf30) takes
// the array on the stack and pops it (stdcall); name unknown.
struct FChannelArray;
void __stdcall DestroyChannelArray_A7BF30(FChannelArray *Array);
struct FChannelArray {
    void *Data;
    int ArrayNum;
    int ArrayMax;
    ~FChannelArray() { DestroyChannelArray_A7BF30(this); }
};

class UEMFChannelTextures : public UnnamedClass30B990 {
public:
    virtual ~UEMFChannelTextures();
    unsigned Pad[11];
    FChannelArray Channels;
};

UEMFChannelTextures::~UEMFChannelTextures() { ConditionalDestroy(); }
