#include "versus_native_properties.h"

UIntProperty::UIntProperty(ECppProperty, INT InOffset, FName InCategory, DWORD InFlags)
    : UProperty(EC_CppProperty, InOffset, InCategory, InFlags)
{}

UBoolProperty::UBoolProperty(ECppProperty, INT InOffset, FName InCategory, DWORD InFlags)
    : UProperty(EC_CppProperty, InOffset, InCategory, InFlags), BitMask(1)
{}

UFloatProperty::UFloatProperty(ECppProperty, INT InOffset, FName InCategory, DWORD InFlags)
    : UProperty(EC_CppProperty, InOffset, InCategory, InFlags)
{}

UStrProperty::UStrProperty(ECppProperty, INT InOffset, FName InCategory, DWORD InFlags)
    : UProperty(EC_CppProperty, InOffset, InCategory, InFlags)
{}

UArrayProperty::UArrayProperty(ECppProperty, INT InOffset, FName InCategory, DWORD InFlags)
    : UProperty(EC_CppProperty, InOffset, InCategory, InFlags)
{}

static const DWORD CPF_NeedCtorLink = 0x00400000;

static inline INT AlignPropertyOffset(INT Offset, INT Alignment)
{
    return (Offset + Alignment - 1) & ~(Alignment - 1);
}

INT UIntProperty::Link(FArchive &Ar, UProperty *Prev)
{
    ElementSize = sizeof(INT);
    Offset = AlignPropertyOffset(static_cast<UField *>(Outer)->GetPropertiesSize(), sizeof(INT));
    return Offset - static_cast<UField *>(Outer)->GetPropertiesSize();
}

INT UFloatProperty::Link(FArchive &Ar, UProperty *Prev)
{
    ElementSize = sizeof(FLOAT);
    Offset = AlignPropertyOffset(static_cast<UField *>(Outer)->GetPropertiesSize(), sizeof(FLOAT));
    return Offset - static_cast<UField *>(Outer)->GetPropertiesSize();
}

INT UNameProperty::Link(FArchive &Ar, UProperty *Prev)
{
    ElementSize = sizeof(FName);
    Offset = AlignPropertyOffset(static_cast<UField *>(Outer)->GetPropertiesSize(), sizeof(FName));
    return Offset - static_cast<UField *>(Outer)->GetPropertiesSize();
}

INT UObjectProperty::Link(FArchive &Ar, UProperty *Prev)
{
    ElementSize = sizeof(UObject *);
    Offset = AlignPropertyOffset(static_cast<UField *>(Outer)->GetPropertiesSize(), sizeof(UObject *));
    if (((PropertyFlags & 0x04000000) && (PropertyFlags & 0x00000008)) ||
        (PropertyClass->ClassFlags & 0x00200000))
        PropertyFlags |= CPF_NeedCtorLink;
    return Offset - static_cast<UField *>(Outer)->GetPropertiesSize();
}
