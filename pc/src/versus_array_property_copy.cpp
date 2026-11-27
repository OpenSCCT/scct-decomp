#include "versus_build.h"
#include "versus_native_properties.h"

void appMemcpy(void *Dest, const void *Src, INT Count);
static const DWORD CPF_CompactArray = 0x80000000;
static const DWORD CPF_NeedCtorLink = 0x00400000;

extern const TCHAR FSArrayAddTag[] = L"FSArray::Add";
extern const TCHAR FSArrayTag[] = L"FSArray";

INT FSArray::Add(INT Count, INT ElementSize)
{
    INT Index = Num;
    Num += Count;
    if (!Data)
        Data = Num * ElementSize > 0
            ? static_cast<BYTE *>(GMalloc->Malloc(Num * ElementSize, FSArrayAddTag)) : 0;
    else
        Data = static_cast<BYTE *>(GMalloc->Realloc(Data, Num * ElementSize, FSArrayTag));
    return Index;
}

void UArrayProperty::CopyCompleteValue(void *Dest, void *Src, UObject *SuperObject)
{
    INT Size = Inner->ElementSize;
    if (PropertyFlags & CPF_CompactArray)
    {
        FSArray *SrcArray = static_cast<FSArray *>(Src);
        FSArray *DestArray = static_cast<FSArray *>(Dest);
        DestArray->Empty();
        if (Inner->PropertyFlags & CPF_NeedCtorLink)
        {
            DestArray->AddZeroed(Size, SrcArray->Num);
            BYTE *SrcData = SrcArray->Data;
            BYTE *DestData = DestArray->Data;
            for (INT i = DestArray->Num; i > 0; i--)
            {
                Inner->CopyCompleteValue(DestData, SrcData, SuperObject);
                DestData += Size;
                SrcData += Size;
            }
        }
        else
        {
            DestArray->Add(SrcArray->Num, Size);
            appMemcpy(DestArray->Data, SrcArray->Data, SrcArray->Num * Size);
        }
    }
    else
    {
        FArray *SrcArray = static_cast<FArray *>(Src);
        FArray *DestArray = static_cast<FArray *>(Dest);
        DestArray->Empty(Size, SrcArray->ArrayNum);
        if (Inner->PropertyFlags & CPF_NeedCtorLink)
        {
            DestArray->AddZeroed(Size, SrcArray->ArrayNum);
            BYTE *SrcData = static_cast<BYTE *>(SrcArray->Data);
            BYTE *DestData = static_cast<BYTE *>(DestArray->Data);
            for (INT i = DestArray->ArrayNum; i > 0; i--)
            {
                Inner->CopyCompleteValue(DestData, SrcData, SuperObject);
                DestData += Size;
                SrcData += Size;
            }
        }
        else
        {
            DestArray->Add(SrcArray->ArrayNum, Size);
            appMemcpy(DestArray->Data, SrcArray->Data, SrcArray->ArrayNum * Size);
        }
    }
}

void UArrayProperty::DestroyValue(void *Dest)
{
    if (Offset == 0 && Outer->IsA(&UClass::PrivateStaticClass))
        return;
    if (PropertyFlags & CPF_CompactArray)
    {
        FSArray *DestArray = static_cast<FSArray *>(Dest);
        if (Inner->PropertyFlags & CPF_NeedCtorLink)
        {
            INT Size = Inner->ElementSize;
            BYTE *DestData = static_cast<BYTE *>(DestArray->Data);
            for (INT i = DestArray->Num; i > 0; i--)
            {
                Inner->DestroyValue(DestData);
                DestData += Size;
            }
        }
        if (DestArray->Data)
        {
            GMalloc->Free(DestArray->Data);
            DestArray->Data = 0;
        }
        DestArray->Num = 0;
    }
    else
    {
        FArray *DestArray = static_cast<FArray *>(Dest);
        if (Inner->PropertyFlags & CPF_NeedCtorLink)
        {
            INT Size = Inner->ElementSize;
            BYTE *DestData = static_cast<BYTE *>(DestArray->Data);
            for (INT i = DestArray->ArrayNum; i > 0; i--)
            {
                Inner->DestroyValue(DestData);
                DestData += Size;
            }
        }
        if (DestArray->Data)
        {
            GMalloc->Free(DestArray->Data);
            DestArray->Data = 0;
        }
        DestArray->ArrayNum = DestArray->ArrayMax = 0;
    }
}
