// UActorChannel destructor (RVA 0xe1c90) from the Steam Versus payload. The
// deleting destructor at 0xe1c60 (UActorChannel) calls this. Its parent is the
// channel class matched as UnnamedClass304548 (0xe1de0, likely UChannel).
// Only the members this destructor touches are declared.
#include "versus_build.h"
#include "unreal_object.h"

enum { INDEX_NONE = -1 };
enum EObjectFlags { RF_Destroyed = 0x00800000, RF_DebugDestroy = 0x80000000 };

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
