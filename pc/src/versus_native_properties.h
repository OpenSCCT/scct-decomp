#ifndef VERSUS_NATIVE_PROPERTIES_H
#define VERSUS_NATIVE_PROPERTIES_H

#include "versus_build.h"
#include "versus_native_class_init.h"

enum ECppProperty { EC_CppProperty };

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

    short ArrayDim;
    short ElementSize;
    DWORD PropertyFlags;
    FName Category;
    INT Offset;
    BYTE unk_40[8];
    UProperty *ConstructorLinkNext;
    UProperty *NextRef;
    BYTE unk_50[8];

    UProperty() : UField(0), ArrayDim(1), NextRef(0) {}
    UProperty(ECppProperty, INT InOffset, FName InCategory, DWORD InFlags);
};

#define DECLARE_NATIVE_PROPERTY(Type) \
    static UClass PrivateStaticClass; \
    void *operator new(unsigned int, UObject *InOuter, FName InName, DWORD Flags = 0) { \
        return StaticAllocateObject(&PrivateStaticClass, InOuter, InName, Flags); \
    } \
    virtual ~Type(); \
    Type(ECppProperty, INT InOffset, FName InCategory, DWORD InFlags)

class UIntProperty : public UProperty { public: DECLARE_NATIVE_PROPERTY(UIntProperty); };
class UBoolProperty : public UProperty {
public:
    DWORD BitMask;
    DECLARE_NATIVE_PROPERTY(UBoolProperty);
};
class UFloatProperty : public UProperty { public: DECLARE_NATIVE_PROPERTY(UFloatProperty); };
class UStrProperty : public UProperty {
public:
    UStrProperty() {}
    DECLARE_NATIVE_PROPERTY(UStrProperty);
};

class UArrayProperty : public UProperty {
public:
    UProperty *Inner;
    DECLARE_NATIVE_PROPERTY(UArrayProperty);
};

class UEnum : public UField {
public:
    static UClass PrivateStaticClass;
    TArray<FName> Names;
    UEnum(UField *InSuper);
    virtual ~UEnum();
    void *operator new(unsigned int, UObject *InOuter, FName InName, DWORD Flags = 0) {
        return StaticAllocateObject(&PrivateStaticClass, InOuter, InName, Flags);
    }
};
class UByteProperty : public UProperty {
public:
    UEnum *Enum;
    static UClass PrivateStaticClass;
    void *operator new(unsigned int, UObject *InOuter, FName InName, DWORD Flags = 0) {
        return StaticAllocateObject(&PrivateStaticClass, InOuter, InName, Flags);
    }
    virtual ~UByteProperty();
    UByteProperty(ECppProperty, INT InOffset, FName InCategory, DWORD InFlags, UEnum *InEnum);
};
#undef DECLARE_NATIVE_PROPERTY
#endif
