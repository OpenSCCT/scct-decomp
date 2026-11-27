// Scalar property serialization, text conversion and object reference cleanup.
#include "versus_build.h"
#include "versus_native_properties.h"
#include "versus_archive.h"

extern "C" __declspec(dllimport) INT __cdecl _wtoi(const TCHAR *Text);
extern "C" __declspec(dllimport) double __cdecl atof(const char *Text);
char *appToAnsi(const TCHAR *Text, char *Dest = 0);
INT appSprintf(TCHAR *Dest, const TCHAR *Format, ...);

extern const TCHAR IntegerValueFormat[] = L"%i";
extern const TCHAR FloatValueFormat[] = L"%f";
extern const TCHAR QualifiedObjectFormat[] = L"%s\xa7(%i)'%s\xa7(%i).%s\xa7(%i)'";
extern const TCHAR ObjectFormat[] = L"%s\xa7(%i)'%s\xa7(%i)'";
extern const TCHAR NoneObjectFormat[] = L"None\xa7(%i)";

static const DWORD CPF_Parm = 0x00000080;

extern TArray<FNameEntry *> FName_Names;

static const TCHAR *NameText(FName Name)
{
    return FName_Names(Name.Index)->Name;
}

UBOOL UIntProperty::Identical(const void *A, const void *B) const
{
    return *static_cast<const INT *>(A) == (B ? *static_cast<const INT *>(B) : 0);
}

UBOOL UFloatProperty::Identical(const void *A, const void *B) const
{
    return *static_cast<const FLOAT *>(A) == (B ? *static_cast<const FLOAT *>(B) : 0.f);
}

UBOOL UObjectProperty::Identical(const void *A, const void *B) const
{
    return *static_cast<UObject *const *>(A) == (B ? *static_cast<UObject *const *>(B) : 0);
}

void UByteProperty::SerializeItem(FArchive &Ar, void *Value, INT MaxReadBytes) const
{
    Ar << *static_cast<BYTE *>(Value);
}

void UIntProperty::SerializeItem(FArchive &Ar, void *Value, INT MaxReadBytes) const
{
    Ar << *static_cast<INT *>(Value);
}

void UFloatProperty::SerializeItem(FArchive &Ar, void *Value, INT MaxReadBytes) const
{
    Ar << *static_cast<FLOAT *>(Value);
}

void UObjectProperty::SerializeItem(FArchive &Ar, void *Value, INT MaxReadBytes) const
{
    Ar << *static_cast<UObject **>(Value);
}

void UNameProperty::SerializeItem(FArchive &Ar, void *Value, INT MaxReadBytes) const
{
    Ar << *static_cast<FName *>(Value);
}

UBOOL UIntProperty::NetSerializeItem(FArchive &Ar, UPackageMap *Map, void *Data) const
{
    if (PropertyFlags & CPF_Parm)
        Ar.SerializeBits(Data, ArrayDim * sizeof(INT) * 8);
    else
        Ar << *static_cast<INT *>(Data);
    return 1;
}

UBOOL UFloatProperty::NetSerializeItem(FArchive &Ar, UPackageMap *Map, void *Data) const
{
    if (PropertyFlags & CPF_Parm)
        Ar.SerializeBits(Data, ArrayDim * sizeof(FLOAT) * 8);
    else
        Ar << *static_cast<FLOAT *>(Data);
    return 1;
}

void UIntProperty::ExportTextItem(TCHAR *Text, BYTE *Value, BYTE *Default, INT PortFlags) const
{
    appSprintf(Text, IntegerValueFormat, *reinterpret_cast<INT *>(Value));
}

void UFloatProperty::ExportTextItem(TCHAR *Text, BYTE *Value, BYTE *Default, INT PortFlags) const
{
    appSprintf(Text, FloatValueFormat, *reinterpret_cast<FLOAT *>(Value));
}

const TCHAR *UIntProperty::ImportText(const TCHAR *Buffer, BYTE *Data, INT PortFlags) const
{
    if (*Buffer == '-' || (*Buffer >= '0' && *Buffer <= '9'))
        *reinterpret_cast<INT *>(Data) = _wtoi(Buffer);
    while (*Buffer == '-' || (*Buffer >= '0' && *Buffer <= '9'))
        ++Buffer;
    return Buffer;
}

const TCHAR *UFloatProperty::ImportText(const TCHAR *Buffer, BYTE *Data, INT PortFlags) const
{
    *reinterpret_cast<FLOAT *>(Data) = static_cast<FLOAT>(atof(appToAnsi(Buffer)));
    while (*Buffer && *Buffer != ',' && *Buffer != ')' && *Buffer != '\r' && *Buffer != '\n')
        ++Buffer;
    return Buffer;
}

void UObjectProperty::CleanupDestroyed(BYTE *Data)
{
    for (INT i = 0; i < ArrayDim; ++i) {
        UObject *&Object = *reinterpret_cast<UObject **>(Data + i * ElementSize);
        if (Object && Object->IsPendingKill())
            Object = 0;
    }
}

void UStrProperty::CopySingleValue(void *Dest, void *Src, UObject *SuperObject)
{
    *static_cast<FString *>(Dest) = *static_cast<FString *>(Src);
}

void UObjectProperty::ExportTextItem(TCHAR *Text, BYTE *Value, BYTE *Default, INT PortFlags) const
{
    UObject *Object = *reinterpret_cast<UObject **>(Value);
    if (Object) {
        if (Object->Outer) {
            FName ClassName = Object->GetClass()->GetFName();
            FName OuterName = Object->Outer->GetFName();
            FName ObjectName = Object->GetFName();
            appSprintf(Text, QualifiedObjectFormat, NameText(ClassName), ClassName.Index,
                NameText(OuterName), OuterName.Index, NameText(ObjectName), ObjectName.Index);
        } else {
            FName ClassName = Object->GetClass()->GetFName();
            FName ObjectName = Object->GetFName();
            appSprintf(Text, ObjectFormat, NameText(ClassName), ClassName.Index,
                NameText(ObjectName), ObjectName.Index);
        }
    } else {
        appSprintf(Text, NoneObjectFormat, NAME_None);
    }
}
