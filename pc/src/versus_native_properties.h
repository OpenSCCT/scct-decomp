#ifndef VERSUS_NATIVE_PROPERTIES_H
#define VERSUS_NATIVE_PROPERTIES_H

#include "versus_build.h"
#include "versus_native_class_init.h"

enum ECppProperty { EC_CppProperty };

class UProperty : public UField {
public:
    virtual ~UProperty();
    virtual void VirtualSlot27();
    virtual INT Link(FArchive &Ar, UProperty *Prev);
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

class UIntProperty : public UProperty {
public:
    DECLARE_NATIVE_PROPERTY(UIntProperty);
    virtual INT Link(FArchive &Ar, UProperty *Prev);
};
class UBoolProperty : public UProperty {
public:
    DWORD BitMask;
    DECLARE_NATIVE_PROPERTY(UBoolProperty);
};
class UFloatProperty : public UProperty {
public:
    DECLARE_NATIVE_PROPERTY(UFloatProperty);
    virtual INT Link(FArchive &Ar, UProperty *Prev);
};
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

class UNameProperty : public UProperty {
public:
    virtual INT Link(FArchive &Ar, UProperty *Prev);
    DECLARE_NATIVE_PROPERTY(UNameProperty);
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
    virtual INT Link(FArchive &Ar, UProperty *Prev);
    UEnum *Enum;
    static UClass PrivateStaticClass;
    void *operator new(unsigned int, UObject *InOuter, FName InName, DWORD Flags = 0) {
        return StaticAllocateObject(&PrivateStaticClass, InOuter, InName, Flags);
    }
    virtual ~UByteProperty();
    UByteProperty(ECppProperty, INT InOffset, FName InCategory, DWORD InFlags, UEnum *InEnum);
};

class UObjectProperty : public UProperty {
public:
    static UClass PrivateStaticClass;
    UClass *PropertyClass;

    void *operator new(unsigned int, UObject *Outer, FName Name, DWORD Flags = 0) {
        return StaticAllocateObject(&PrivateStaticClass, Outer, Name, Flags);
    }
    virtual ~UObjectProperty();
    virtual INT Link(FArchive &Ar, UProperty *Prev);
    UObjectProperty(ECppProperty, INT InOffset, FName InCategory, DWORD InFlags, UClass *InClass)
        : UProperty(EC_CppProperty, InOffset, InCategory, InFlags), PropertyClass(InClass) {}
};

class UStructProperty : public UProperty {
public:
    static UClass PrivateStaticClass;
    UStruct *Struct;

    void *operator new(unsigned int, UObject *Outer, FName Name, DWORD Flags = 0) {
        return StaticAllocateObject(&PrivateStaticClass, Outer, Name, Flags);
    }
    virtual ~UStructProperty();
    UStructProperty(ECppProperty, INT InOffset, FName InCategory, DWORD InFlags, UStruct *InStruct)
        : UProperty(EC_CppProperty, InOffset, InCategory, InFlags), Struct(InStruct) {}
};

#undef DECLARE_NATIVE_PROPERTY
#endif
