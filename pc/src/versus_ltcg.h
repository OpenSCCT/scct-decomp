// versus_ltcg.h -- array members whose element type or destructor convention is still open
//
// Element types. Only their size is known, from the FArray::Remove call each array destructor
// makes; a type named after an RVA is one whose elements have the destructor at that RVA.
//
// TArrayLtcg. The Versus executable was linked with whole-program optimisation: methods such as
// the TArray<FString>::Remove at RVA 0xc7d0 take an argument in EDI, which no compiler-only
// build produces. The same optimisation gave many TArray<T> destructors a private convention:
// `this` on the stack, popped by the callee. A unit compiled alone cannot make that choice, so
// those members are spelled with TArrayLtcg, whose destructor passes `this` to a __stdcall
// function that stands for TArray<T>::~TArray. FAKEMATCH: the original source is a TArray<T>
// member. Every destructor that destroys a TArrayLtcg member stays MATCH-PENDING until the
// link-time convention can be reproduced.
#ifndef VERSUS_LTCG_H
#define VERSUS_LTCG_H

#include "unreal_types.h"
#include "unreal_containers.h"

struct UnkType_4 { BYTE unk_0[0x4]; };
struct UnkType_8 { BYTE unk_0[0x8]; };
struct UnkType_C { BYTE unk_0[0xc]; };
struct UnkType_10 { BYTE unk_0[0x10]; };
struct UnkType_14 { BYTE unk_0[0x14]; };
struct UnkType_18 { BYTE unk_0[0x18]; };
struct UnkType_1C { BYTE unk_0[0x1c]; };
struct UnkType_20 { BYTE unk_0[0x20]; };
struct UnkType_24 { BYTE unk_0[0x24]; };
struct UnkType_28 { BYTE unk_0[0x28]; };
struct UnkType_E4 { BYTE unk_0[0xe4]; };

// elements removed through the second FArray remove function, at RVA 0x11aa0
struct UnkType_8_911AA0 { BYTE unk_0[0x8]; };
struct UnkType_C8_911AA0 { BYTE unk_0[0xc8]; };

// elements with a destructor
struct UnkType_9A3370 { BYTE unk_0[0x14]; ~UnkType_9A3370(); };
struct UnkType_163C20 { BYTE unk_0[0x1c]; ~UnkType_163C20(); };
struct UnkType_179000 { BYTE unk_0[0x6c]; ~UnkType_179000(); };
struct UnkType_1EE640 { BYTE unk_0[0x48]; ~UnkType_1EE640(); };
struct UnkType_1EECB0 { BYTE unk_0[0x18]; ~UnkType_1EECB0(); };
struct UnkType_1EEFB0 { BYTE unk_0[0x18]; ~UnkType_1EEFB0(); };

// USound's member at 0x28: an object with the vtable at RVA 0x308b00 that owns a byte array.
class UnkType_308B00 {
public:
    ~UnkType_308B00();
    BYTE unk_0[0x18];
};

// FAKEMATCH: stands for a TArray<T> member whose destructor has a link-time calling convention.
template<class T> class TArrayLtcg {
public:
    T  *Data;
    INT ArrayNum;
    INT ArrayMax;
    ~TArrayLtcg();
};

template<class T> void __stdcall LtcgArrayDestructor(TArrayLtcg<T> *Array);

// TArrayLtcg::~TArrayLtcg
template<class T> inline TArrayLtcg<T>::~TArrayLtcg()
{
    // part of the stand-in: retail loads every such `this` through EAX, which the compiler
    // only does here when the pointer is first copied to a local
    TArrayLtcg *This = this;
    LtcgArrayDestructor(This);
}

#endif // VERSUS_LTCG_H
