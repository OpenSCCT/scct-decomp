// unreal_field.h -- UField and the script structure classes built on it
#ifndef UNREAL_FIELD_H
#define UNREAL_FIELD_H

#include "unreal_object.h"

#ifdef SCCT_VERSUS

// Core.Field: 0x30 bytes, 27 virtual functions
class UField : public UObject {
public:
    virtual ~UField();
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();

    BYTE unk_28[0x8];
};

// Core.Struct: 0x68 bytes, 34 virtual functions
class UStruct : public UField {
public:
    virtual ~UStruct();
    virtual void VirtualSlot27();
    virtual void VirtualSlot28();
    virtual void VirtualSlot29();
    virtual void VirtualSlot30();
    virtual void VirtualSlot31();
    virtual void VirtualSlot32();
    virtual void VirtualSlot33();

    BYTE unk_30[0x38];
};

// Core.State: 0x88 bytes, 34 virtual functions
class UState : public UStruct {
public:
    virtual ~UState();

    BYTE unk_68[0x20];
};

#else // Campaign
#include "unreal_containers.h"

// Core.Field: 0x34 bytes, 28 virtual functions
class UField : public UObject {
public:
    virtual ~UField();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();

    UField *SuperField;         // the class or struct this one extends
    BYTE    unk_2c[0x8];
};

// Core.Struct: 0x6c bytes, 35 virtual functions
class UStruct : public UField {
public:
    virtual ~UStruct();
    virtual void VirtualSlot28();
    virtual void VirtualSlot29();
    virtual void VirtualSlot30();
    virtual void VirtualSlot31();
    virtual void VirtualSlot32();
    virtual void VirtualSlot33();
    virtual void VirtualSlot34();

    BYTE         unk_34[0x18];
    INT          PropertiesSize;    // bytes of one instance
    TArray<BYTE> Script;            // bytecode
    BYTE         unk_5c[0x10];

    UBOOL StructCompare(const void *A, const void *B);
};

// Core.State: 0x284 bytes, 35 virtual functions
class UState : public UStruct {
public:
    virtual ~UState();

    BYTE unk_6c[0x218];

    UState *GetSuperState() const { return (UState *)SuperField; }
};

#endif // SCCT_VERSUS

#endif // UNREAL_FIELD_H
