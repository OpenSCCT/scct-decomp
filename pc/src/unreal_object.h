// unreal_object.h -- UObject, the root of the engine's object classes
#ifndef UNREAL_OBJECT_H
#define UNREAL_OBJECT_H

#include "unreal_types.h"

struct FGuid;

// UObject::ObjectFlags bits. The names are open: no symbol evidence names these bits.
enum {
    ObjectFlag_00800000 = 0x00800000,   // ConditionalDestroy has run for this object
    ObjectFlag_80000000 = 0x80000000    // cleared when ConditionalDestroy runs
};

// The COM-style root of UObject: three __stdcall methods at the head of every object vtable.
class FUnknown {
public:
    virtual DWORD __stdcall QueryInterface(const FGuid &RefIID, void **InterfacePtr);
    virtual DWORD __stdcall AddRef();
    virtual DWORD __stdcall Release();
};

// Core.Object: 0x28 bytes. 22 virtual functions in the Versus executable, 24 in Campaign.
// Slots 0 to 3 and 9 hold the same functions in both; the other slots are not identified yet.
class UObject : public FUnknown {
public:
    virtual ~UObject();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void Destroy();
    virtual void VirtualSlot10();
    virtual void VirtualSlot11();
    virtual void VirtualSlot12();
    virtual void VirtualSlot13();
    virtual void VirtualSlot14();
    virtual void VirtualSlot15();
    virtual void VirtualSlot16();
    virtual void VirtualSlot17();
    virtual void VirtualSlot18();
    virtual void VirtualSlot19();
    virtual void VirtualSlot20();
    virtual void VirtualSlot21();
#ifndef SCCT_VERSUS
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
#endif

    INT   Index;            // -1 while the object is not in the object table
    BYTE  unk_8[0x14];
    DWORD ObjectFlags;      // ObjectFlag_ bits
    BYTE  unk_20[0x8];

    // Destroys the object once: marks it, then calls Destroy.
    INT ConditionalDestroy()
    {
        if (Index != -1 && !(ObjectFlags & ObjectFlag_00800000)) {
            ObjectFlags = (ObjectFlags & ~(ObjectFlag_80000000 | ObjectFlag_00800000))
                | ObjectFlag_00800000;
            Destroy();
            return 1;
        }
        return 0;
    }
};

#endif // UNREAL_OBJECT_H
