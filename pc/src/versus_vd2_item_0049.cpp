// Versus RVA 0xcd20: destructor of an Unreal Engine 2 class whose vtable is at
// image-base-relative 0x30d2f8 (named UnnamedClass30D2F8 since no registered
// constructor identifies it). Its parent is UnnamedClass30D6A0 (destructor at
// RVA 0xcc80); it owns one member at 0x3c with an out-of-line destructor
// (RVA 0xf2c0). Like every DECLARE_CLASS destructor it first runs
// UObject::ConditionalDestroy().
#include "versus_build.h"
#include "unreal_object.h"

enum { INDEX_NONE = -1 };
enum EObjectFlags { RF_Destroyed = 0x00800000, RF_DebugDestroy = 0x80000000 };

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
