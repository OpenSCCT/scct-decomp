#ifndef VERSUS_MATERIAL_H
#define VERSUS_MATERIAL_H

#include "versus_build.h"
#ifndef VERSUS_NATIVE_CLASS_TYPES_H
#include "unreal_object.h"
#endif

// Engine.Material: 0x4c bytes, 35 virtual functions
class UMaterial : public UObject {
public:
    virtual ~UMaterial();
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual INT MaterialUSize();
    virtual INT MaterialVSize();
    virtual void VirtualSlot28();
    virtual void VirtualSlot29();
    virtual void VirtualSlot30();
    virtual void VirtualSlot31();
    virtual void VirtualSlot32();
    virtual void VirtualSlot33();
    virtual void VirtualSlot34();

    BYTE unk_28[0x24];
};

#endif
