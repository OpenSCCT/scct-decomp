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
class UClass : public UState {
public:
    virtual ~UClass();

    BYTE         unk_284[0x18];
    TArray<BYTE> Defaults;      // the class's default property values
    BYTE         unk_2a8[0x38];

    UClass *GetSuperClass() const { return (UClass *)SuperField; }
};

// UObject::IsA: whether the object's class is SomeBase or derives from it
inline UBOOL UObject::IsA(UClass *SomeBase) const
{
    for (UClass *TempClass = Class; TempClass; TempClass = TempClass->GetSuperClass())
        if (TempClass == SomeBase)
            return 1;
    return SomeBase == 0;
}

// A class whose class object is created on first use.
#define DECLARE_LAZY_CLASS(Name)                                            \
    static UClass *PrivateStaticClass;                                      \
    static UClass *GetPrivateStaticClass##Name(const TCHAR *Package);       \
    static void InitializePrivateStaticClass##Name();                       \
    static UClass *StaticClass()                                            \
    {                                                                       \
        if (!PrivateStaticClass)                                            \
        {                                                                   \
            PrivateStaticClass = GetPrivateStaticClass##Name(L"Engine");    \
            InitializePrivateStaticClass##Name();                           \
        }                                                                   \
        return PrivateStaticClass;                                          \
    }

#endif // SCCT_VERSUS

#endif // UNREAL_CLASS_H
