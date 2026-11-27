#ifndef VERSUS_NATIVE_PROPERTIES_H
#define VERSUS_NATIVE_PROPERTIES_H

#include "versus_build.h"
#include "versus_native_class_init.h"

#include "versus_property.h"

inline UProperty::UProperty() : UField(0), ArrayDim(1), NextRef(0) {}

#define DECLARE_NATIVE_PROPERTY(Type) \
    static UClass PrivateStaticClass; \
    void *operator new(unsigned int, UObject *InOuter, FName InName, DWORD Flags = 0) { \
        return StaticAllocateObject(&PrivateStaticClass, InOuter, InName, Flags); \
    } \
    virtual ~Type(); \
    Type(ECppProperty, INT InOffset, FName InCategory, DWORD InFlags)

class UIntProperty : public UProperty {
public:
    virtual UBOOL Identical(const void *A, const void *B) const;
    virtual void SerializeItem(FArchive &Ar, void *Value, INT MaxReadBytes) const;
    virtual UBOOL NetSerializeItem(FArchive &Ar, UPackageMap *Map, void *Data) const;
    virtual void ExportTextItem(TCHAR *Text, BYTE *Value, BYTE *Default, INT PortFlags) const;
    virtual const TCHAR *ImportText(const TCHAR *Buffer, BYTE *Data, INT PortFlags) const;
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
    virtual UBOOL Identical(const void *A, const void *B) const;
    virtual void SerializeItem(FArchive &Ar, void *Value, INT MaxReadBytes) const;
    virtual UBOOL NetSerializeItem(FArchive &Ar, UPackageMap *Map, void *Data) const;
    virtual void ExportTextItem(TCHAR *Text, BYTE *Value, BYTE *Default, INT PortFlags) const;
    virtual const TCHAR *ImportText(const TCHAR *Buffer, BYTE *Data, INT PortFlags) const;
    DECLARE_NATIVE_PROPERTY(UFloatProperty);
    virtual INT Link(FArchive &Ar, UProperty *Prev);
};
class UStrProperty : public UProperty {
public:
    virtual void CopySingleValue(void *Dest, void *Src, UObject *SuperObject);
    UStrProperty() {}
    DECLARE_NATIVE_PROPERTY(UStrProperty);
};

class UArrayProperty : public UProperty {
public:
    UProperty *Inner;
    virtual void CopyCompleteValue(void *Dest, void *Src, UObject *SuperObject);
    virtual void DestroyValue(void *Dest);
    DECLARE_NATIVE_PROPERTY(UArrayProperty);
};

class UNameProperty : public UProperty {
public:
    virtual void SerializeItem(FArchive &Ar, void *Value, INT MaxReadBytes) const;
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
    virtual void SerializeItem(FArchive &Ar, void *Value, INT MaxReadBytes) const;
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
    virtual void CopyCompleteValue(void *Dest, void *Src, UObject *SuperObject);
    virtual void CleanupDestroyed(BYTE *Data);
    virtual UBOOL Identical(const void *A, const void *B) const;
    virtual void SerializeItem(FArchive &Ar, void *Value, INT MaxReadBytes) const;
    virtual void ExportTextItem(TCHAR *Text, BYTE *Value, BYTE *Default, INT PortFlags) const;
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
    virtual void CleanupDestroyed(BYTE *Data);
    static UClass PrivateStaticClass;
    UStruct *Struct;
    virtual UBOOL Identical(const void *A, const void *B) const;
    virtual void SerializeItem(FArchive &Ar, void *Value, INT MaxReadBytes) const;
    virtual void DestroyValue(void *Dest);

    void *operator new(unsigned int, UObject *Outer, FName Name, DWORD Flags = 0) {
        return StaticAllocateObject(&PrivateStaticClass, Outer, Name, Flags);
    }
    virtual ~UStructProperty();
    UStructProperty(ECppProperty, INT InOffset, FName InCategory, DWORD InFlags, UStruct *InStruct)
        : UProperty(EC_CppProperty, InOffset, InCategory, InFlags), Struct(InStruct) {}
};

class UFixedArrayProperty : public UProperty {
public:
    UProperty *Inner;
    INT Count;
    virtual UBOOL Identical(const void *A, const void *B) const;
    virtual void SerializeItem(FArchive &Ar, void *Value, INT MaxReadBytes) const;
    virtual void ExportTextItem(TCHAR *Text, BYTE *Value, BYTE *Default, INT PortFlags) const;
};

class UMapProperty : public UProperty {
public:
    UProperty *Key;
    UProperty *Value;
    virtual const TCHAR *ImportText(const TCHAR *Buffer, BYTE *Data, INT PortFlags) const;
};

#include "versus_script_delegate.h"

class UDelegateProperty : public UProperty {
public:
    virtual INT Link(FArchive &Ar, UProperty *Prev);
    virtual void CopyCompleteValue(void *Dest, void *Src, UObject *SuperObject);
};

#undef DECLARE_NATIVE_PROPERTY
#endif
