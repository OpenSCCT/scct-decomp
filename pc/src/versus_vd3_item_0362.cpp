// Destructor of a UPrimitive-derived class from the Steam Versus payload. Its
// placement constructor does not identify the vtable (0x30B8A0 relative to the
// image base), so the class is named UnnamedClass30B8A0. Like every
// DECLARE_CLASS destructor it runs UObject::ConditionalDestroy(), then its
// members are destroyed in reverse order, then UPrimitive's destructor runs.
// Member release helpers are named after their RVAs.
#include "versus_build.h"
#include "unreal_object.h"

enum { INDEX_NONE = -1 };
enum EObjectFlags { RF_Destroyed = 0x00800000, RF_DebugDestroy = 0x80000000 };

class UPrimitive : public UObject { public: virtual ~UPrimitive(); };

template<unsigned Size> struct InheritedData { unsigned char Bytes[Size]; };

void __stdcall Release_09e800(void *member);
void __stdcall Release_0eecc0(void *member);
void __stdcall Release_0fb4d0(void *member);
void __stdcall Release_0edf20(void *member);
void __stdcall Release_079600(void *member);

class UnnamedClass30B8A0 : public UPrimitive {
public:
    struct Member70 { unsigned char Bytes[0xc]; ~Member70() { Release_09e800(this); } };
    struct Member7C { unsigned char Bytes[0xc]; ~Member7C() { Release_0eecc0(this); } };
    struct ArrayB4D0 { unsigned char Bytes[0xc]; ~ArrayB4D0() { Release_0fb4d0(this); } };
    struct MemberA0 { unsigned char Bytes[0xc]; ~MemberA0() { Release_0edf20(this); } };
    struct Member11C { unsigned char Bytes[0xc]; ~Member11C() { Release_079600(this); } };
    virtual ~UnnamedClass30B8A0();
    InheritedData<0x70 - sizeof(UPrimitive)> UPrimitiveData;
    Member70 Field70;
    Member7C Field7C;
    ArrayB4D0 Field88;
    ArrayB4D0 Field94;
    MemberA0 FieldA0;
    ArrayB4D0 FieldAC;
    unsigned char DataB8[0x11c - 0xb8];
    Member11C Field11C;
};
UnnamedClass30B8A0::~UnnamedClass30B8A0() { ConditionalDestroy(); }
