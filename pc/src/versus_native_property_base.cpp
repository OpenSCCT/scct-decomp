#include "versus_native_properties.h"

UProperty::UProperty(ECppProperty, INT InOffset, FName InCategory, DWORD InFlags)
    : UField(0), ArrayDim(1), PropertyFlags(InFlags), Category(InCategory),
      Offset(InOffset), NextRef(0)
{
    static_cast<UField *>(Outer)->AddCppProperty(this);
}

INT UByteProperty::Link(FArchive &Ar, UProperty *Prev)
{
    ElementSize = sizeof(BYTE);
    Offset = static_cast<UField *>(Outer)->GetPropertiesSize();
    return Offset - static_cast<UField *>(Outer)->GetPropertiesSize();
}
