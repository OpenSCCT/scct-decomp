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

#endif // SCCT_VERSUS

#endif // UNREAL_CLASS_H
