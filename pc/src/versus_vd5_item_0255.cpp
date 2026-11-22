// Destructor at RVA 0xf4af0 of a material class deriving from UnnamedClass309E00
// (vtable 0x10c03f10, so named UnnamedClass303F10 after its vtable relative to the
// image base). It runs UObject::ConditionalDestroy(), destroys a member at +0x70
// through a stdcall helper (FUN_109f4d30), then runs the parent destructor.
#include "versus_build.h"
#include "unreal_object.h"

enum { INDEX_NONE = -1 };
enum EObjectFlags { RF_Destroyed = 0x00800000, RF_DebugDestroy = 0x80000000 };

template<unsigned Size> struct InheritedData { unsigned char Bytes[Size]; };

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
