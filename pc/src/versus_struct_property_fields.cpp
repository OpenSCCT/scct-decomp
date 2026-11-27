#include "versus_native_properties.h"
#include "versus_archive.h"

static const EName NAME_Vector = (EName)87;
static const EName NAME_Rotator = (EName)88;
static const EName NAME_Color = (EName)90;
enum { CLASS_IsAUProperty = 0x8000 };

template<class T> class TFieldIterator {
    UStruct *Struct;
    UField *Field;
public:
    TFieldIterator(UStruct *InStruct)
        : Struct(InStruct), Field(InStruct ? InStruct->Children : 0) { IterateToNext(); }
    operator UBOOL() const { return Field != 0; }
    T *operator->() const { return (T *)Field; }
    void operator++() { Field = Field->Next; IterateToNext(); }
    void IterateToNext();
};

template<> void TFieldIterator<UProperty>::IterateToNext()
{
    while (Struct) {
        while (Field) {
            if (Field->Class->ClassFlags & CLASS_IsAUProperty)
                return;
            Field = Field->Next;
        }
        Struct = Struct->GetInheritanceSuper();
        if (Struct)
            Field = Struct->Children;
    }
}

UBOOL UStructProperty::Identical(const void *A, const void *B) const
{
    for (TFieldIterator<UProperty> It(Struct); It; ++It)
        for (INT i = 0; i < It->ArrayDim; ++i)
            if (!It->Matches(A, B, i))
                return 0;
    return 1;
}

void UStructProperty::DestroyValue(void *Dest)
{
    if (Struct)
        for (UProperty *P = Struct->ConstructorLink; P; P = P->ConstructorLinkNext) {
            if (ArrayDim <= 0) {
                P->DestroyValue((BYTE *)Dest + P->Offset);
            } else {
                for (INT i = 0; i < ArrayDim; ++i)
                    P->DestroyValue((BYTE *)Dest + (i * ElementSize + P->Offset));
            }
        }
}

void UStructProperty::SerializeItem(FArchive &Ar, void *Value, INT MaxReadBytes) const
{
    if ((Ar.IsLoading() || Ar.IsSaving()) && Ar.Ver() >= 118
        && Struct->GetFName() != NAME_Vector && Struct->GetFName() != NAME_Rotator
        && Struct->GetFName() != NAME_Color) {
        Struct->SerializeTaggedProperties(Ar, (BYTE *)Value, 0);
    } else {
        Ar.Preload(Struct);
        Struct->SerializeBin(Ar, (BYTE *)Value, MaxReadBytes);
    }
}

UBOOL UFixedArrayProperty::Identical(const void *A, const void *B) const
{
    for (INT i = 0; i < Count; ++i)
        if (!Inner->Identical((const BYTE *)A + i * Inner->ElementSize,
                B ? (const BYTE *)B + i * Inner->ElementSize : 0))
            return 0;
    return 1;
}
