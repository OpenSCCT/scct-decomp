#include "versus_build.h"
#include "versus_native_properties.h"

extern "C" __declspec(dllimport) unsigned int __cdecl wcslen(const TCHAR *Text);

static const INT PPF_Delimited = 2;

void UFixedArrayProperty::SerializeItem(FArchive &Ar, void *Value, INT MaxReadBytes) const
{
    for (INT i = 0; i < Count; ++i)
        Inner->SerializeItem(Ar, static_cast<BYTE *>(Value) + i * Inner->ElementSize,
            MaxReadBytes > 0 ? MaxReadBytes / Count : 0);
}

void UFixedArrayProperty::ExportTextItem(TCHAR *Text, BYTE *Value, BYTE *Default, INT PortFlags) const
{
    *Text++ = '(';
    for (INT i = 0; i < Count; ++i) {
        if (i > 0)
            *Text++ = ',';
        Inner->ExportTextItem(Text, Value + i * Inner->ElementSize,
            Default ? Default + i * Inner->ElementSize : 0, PortFlags | PPF_Delimited);
        Text += wcslen(Text);
    }
    *Text++ = ')';
    *Text = 0;
}

const TCHAR *UMapProperty::ImportText(const TCHAR *Buffer, BYTE *Data, INT PortFlags) const
{
    return Buffer;
}

void UStructProperty::CleanupDestroyed(BYTE *Data)
{
    for (INT i = 0; i < ArrayDim; ++i)
        Struct->DestroyStructData(Data + i * ElementSize);
}
