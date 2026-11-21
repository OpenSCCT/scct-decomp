// unreal_property.h -- UProperty and the property classes
#ifndef UNREAL_PROPERTY_H
#define UNREAL_PROPERTY_H

#include "unreal_field.h"

#ifdef SCCT_VERSUS

// Core.Property: 0x58 bytes, 40 virtual functions
class UProperty : public UField {
public:
    virtual ~UProperty();
    virtual void VirtualSlot27();
    virtual void VirtualSlot28();
    virtual void VirtualSlot29();
    virtual void VirtualSlot30();
    virtual void VirtualSlot31();
    virtual void VirtualSlot32();
    virtual void VirtualSlot33();
    virtual void VirtualSlot34();
    virtual void VirtualSlot35();
    virtual void VirtualSlot36();
    virtual void VirtualSlot37();
    virtual void VirtualSlot38();
    virtual void VirtualSlot39();

    BYTE unk_30[0x28];
};

// Core.ByteProperty: 0x5c bytes, 40 virtual functions
class UByteProperty : public UProperty {
public:
    virtual ~UByteProperty();

    BYTE unk_58[0x4];
};

// Core.IntProperty: 0x58 bytes, 40 virtual functions
class UIntProperty : public UProperty {
public:
    virtual ~UIntProperty();
};

// Core.DelegateProperty: 0x5c bytes, 40 virtual functions
class UDelegateProperty : public UProperty {
public:
    virtual ~UDelegateProperty();

    BYTE unk_58[0x4];
};

// Core.BoolProperty: 0x5c bytes, 40 virtual functions
class UBoolProperty : public UProperty {
public:
    virtual ~UBoolProperty();

    BYTE unk_58[0x4];
};

// Core.FloatProperty: 0x58 bytes, 40 virtual functions
class UFloatProperty : public UProperty {
public:
    virtual ~UFloatProperty();
};

// Core.ObjectProperty: 0x5c bytes, 40 virtual functions
class UObjectProperty : public UProperty {
public:
    virtual ~UObjectProperty();

    BYTE unk_58[0x4];
};

// Core.ClassProperty: 0x60 bytes, 40 virtual functions
class UClassProperty : public UObjectProperty {
public:
    virtual ~UClassProperty();

    BYTE unk_5c[0x4];
};

// Core.NameProperty: 0x58 bytes, 40 virtual functions
class UNameProperty : public UProperty {
public:
    virtual ~UNameProperty();
};

// Core.StrProperty: 0x58 bytes, 40 virtual functions
class UStrProperty : public UProperty {
public:
    virtual ~UStrProperty();
};

// Core.FixedArrayProperty: 0x60 bytes, 40 virtual functions
class UFixedArrayProperty : public UProperty {
public:
    virtual ~UFixedArrayProperty();

    BYTE unk_58[0x8];
};

// Core.ArrayProperty: 0x5c bytes, 40 virtual functions
class UArrayProperty : public UProperty {
public:
    virtual ~UArrayProperty();

    BYTE unk_58[0x4];
};

// Core.MapProperty: 0x60 bytes, 40 virtual functions
class UMapProperty : public UProperty {
public:
    virtual ~UMapProperty();

    BYTE unk_58[0x8];
};

// Core.StructProperty: 0x5c bytes, 40 virtual functions
class UStructProperty : public UProperty {
public:
    virtual ~UStructProperty();

    BYTE unk_58[0x4];
};

#endif // SCCT_VERSUS

#endif // UNREAL_PROPERTY_H
