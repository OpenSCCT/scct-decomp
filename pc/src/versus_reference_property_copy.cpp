#include "versus_build.h"
#include "versus_native_properties.h"

static const DWORD CPF_NeedCtorLink = 0x00400000;

template<class T> inline T *Cast(UObject *Object)
{
    return Object && Object->IsA(&T::PrivateStaticClass) ? static_cast<T *>(Object) : 0;
}

INT UDelegateProperty::Link(FArchive &Ar, UProperty *Prev)
{
    ElementSize = sizeof(FScriptDelegate);
    Offset = (static_cast<UField *>(Outer)->GetPropertiesSize() + 3) & ~3;
    PropertyFlags |= CPF_NeedCtorLink;
    return Offset - static_cast<UField *>(Outer)->GetPropertiesSize();
}

void UDelegateProperty::CopyCompleteValue(void *Dest, void *Src, UObject *SuperObject)
{
    FScriptDelegate *DestValue = static_cast<FScriptDelegate *>(Dest);
    const FScriptDelegate *SrcValue = static_cast<const FScriptDelegate *>(Src);
    if (SuperObject) {
        if (ArrayDim == 1) {
            UClass *SourceClass = Cast<UClass>(SrcValue->Object);
            DestValue->FunctionName = SrcValue->FunctionName;
            DestValue->Object = SourceClass && SuperObject->IsA(SourceClass)
                ? SuperObject : SrcValue->Object;
        } else {
            for (INT i = 0; i < ArrayDim; i++) {
                UClass *SourceClass = Cast<UClass>(SrcValue[i].Object);
                DestValue[i].FunctionName = SrcValue[i].FunctionName;
                DestValue[i].Object = SourceClass && SuperObject->IsA(SourceClass)
                    ? SuperObject : SrcValue[i].Object;
            }
        }
    } else if (ArrayDim == 1) {
        *DestValue = *SrcValue;
    } else {
        for (INT i = 0; i < ArrayDim; i++)
            DestValue[i] = SrcValue[i];
    }
}

inline UObject *UObject::StaticConstructObject(UClass *InClass, UObject *InOuter, FName InName,
    DWORD SetFlags, UObject *InTemplate, FOutputDevice *Error, UObject *SubobjectRoot)
{
    UObject *Result = StaticAllocateObject(InClass, InOuter, InName, SetFlags,
        InTemplate, Error, 0, SubobjectRoot);
    if (Result)
        InClass->ClassConstructor(Result);
    return Result;
}

void UObjectProperty::CopyCompleteValue(void *Dest, void *Src, UObject *SuperObject)
{
    UObject **DestValue = static_cast<UObject **>(Dest);
    UObject *const *SrcValue = static_cast<UObject *const *>(Src);
    if ((PropertyFlags & CPF_NeedCtorLink) && SuperObject) {
        for (INT i = 0; i < ArrayDim; i++) {
            if (SrcValue[i])
                DestValue[i] = UObject::StaticConstructObject(SrcValue[i]->GetClass(),
                    SuperObject->Outer, NAME_None, 0, SrcValue[i], GError, SuperObject);
            else
                DestValue[i] = SrcValue[i];
        }
    } else {
        for (INT i = 0; i < ArrayDim; i++)
            DestValue[i] = SrcValue[i];
    }
}
