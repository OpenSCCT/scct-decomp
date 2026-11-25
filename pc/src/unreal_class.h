// unreal_class.h -- UClass
#ifndef UNREAL_CLASS_H
#define UNREAL_CLASS_H

#include "unreal_containers.h"
#include "unreal_field.h"

#ifdef SCCT_VERSUS
#include "versus_ltcg.h"

// Core.Class: 0x114 bytes, 34 virtual functions
class UClass : public UState {
public:
    virtual ~UClass();

    BYTE              unk_88[0xc];
    TArray<UnkType_8> unk_94;
    TArray<UnkType_4> unk_a0;
    TArray<BYTE>      unk_ac;
    BYTE              unk_b8[0x10];
    FString           unk_c8;
    TArray<UnkType_C> unk_d4;
    TArray<UnkType_4> unk_e0;
    TArray<UnkType_4> unk_ec;
    TArray<UnkType_4> unk_f8;
    BYTE              unk_104[0x10];
};

#else // Campaign

// Core.Class: 0x2e0 bytes, 35 virtual functions
enum { ClassFlag_00004000 = 0x4000 };   // suppresses the class default object

class UClass : public UState {
public:
    virtual ~UClass();

    DWORD        ClassFlags;
    BYTE         unk_288[0x14];
    TArray<BYTE> Defaults;      // the class's default property values
    BYTE         unk_2a8[0x38];

    UClass *GetSuperClass() const { return (UClass *)SuperField; }
    UObject *GetDefaultObject() const
    {
        return (ClassFlags & ClassFlag_00004000) ? 0 : (UObject *)Defaults.Data;
    }

    DECLARE_LAZY_CLASS_IN(UClass, L"Core")
};

// UObject::IsA: whether the object's class is SomeBase or derives from it
inline UBOOL UObject::IsA(UClass *SomeBase) const
{
    for (UClass *TempClass = Class; TempClass; TempClass = TempClass->GetSuperClass())
        if (TempClass == SomeBase)
            return 1;
    return SomeBase == 0;
}

inline void UObject::operator delete(void *Object)
{
    GMalloc->Free(Object);
}

// The object as a T, or 0 when it is not one.
template<class T> T *Cast(UObject *Src)
{
    return Src && Src->IsA(T::StaticClass()) ? (T *)Src : 0;
}

#endif // SCCT_VERSUS

#endif // UNREAL_CLASS_H
