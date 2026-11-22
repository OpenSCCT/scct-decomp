// Destructor of an AInfo subclass at Versus RVA 0xade10 (vtable 0x10c05170).
// The class name is not recovered; UnnamedInfo_ade10 is a neutral name.
// Like every DECLARE_CLASS destructor, it runs UObject::ConditionalDestroy()
// and then the members' destructors and AInfo's destructor.
#include "versus_build.h"
#include "unreal_object.h"

enum { INDEX_NONE = -1 };
enum EObjectFlags { RF_Destroyed = 0x00800000, RF_DebugDestroy = 0x80000000 };

class AInfo : public UObject { public: virtual ~AInfo(); };

class FString {
public:
    ~FString();
    unsigned short *Data;
    int ArrayNum;
    int ArrayMax;
};

template<unsigned Size> struct InheritedData { unsigned char Bytes[Size]; };
// Releases a member's storage (retail helper 0x10aeecc0, takes the member on the stack).
void __stdcall ReleaseMember3D4(void *member);

class UnnamedInfo_ade10 : public AInfo {
public:
    struct Released3D4 { ~Released3D4() { Released3D4 *self = this; ReleaseMember3D4(self); } };
    // 12-byte element with an out-of-line destructor (retail 0x10a79000).
    struct Entry { ~Entry(); unsigned char Bytes[12]; };
    virtual ~UnnamedInfo_ade10();
    InheritedData<0x314 - sizeof(AInfo)> AInfoData;
    FString Field314;
    FString Field320;
    FString Field32C;
    FString Field338;
    FString Field344;
    FString Field350;
    FString Field35C;
    FString Field368;
    unsigned char Data374[0x388 - 0x374];
    FString Field388;
    FString Field394;
    unsigned char Data3A0[0x3d4 - 0x3a0];
    Released3D4 Field3D4;
    unsigned char Data3D5[0x3e4 - 0x3d5];
    FString Field3E4;
    FString Field3F0;
    FString Field3FC;
    Entry Field408[11];
    Entry Field48C[2];
};
UnnamedInfo_ade10::~UnnamedInfo_ade10() { ConditionalDestroy(); }
