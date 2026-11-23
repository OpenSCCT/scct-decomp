// campaign_leaf_580130.cpp -- constructor at VA 0x10e80130: runs the base class constructor at VA
// 0x10e809c0, installs this class's vtable (VA 0x1114efcc), constructs the empty arrays at 0x104
// and 0x110, calls the base method at VA 0x10e80900, stores its argument at 0xe0 and counts the
// instance in the global at VA 0x111cf4d0. The class names are invented; the addresses are the
// binary's.

#include "campaign_global_111cf4d0.h"

class UnkType_10e80130_10e809c0
{
public:
    UnkType_10e80130_10e809c0();

    virtual void VirtualSlot0();

    void Unk_10e80900();

private:
    int unk_04[0xdc / 4];
};

struct UnkType_10e80130_Array
{
    // UnkType_10e80130_Array::UnkType_10e80130_Array
    UnkType_10e80130_Array()
        : unk_00(0), unk_04(0), unk_08(0x80000000)
    {
    }

    void* unk_00;
    int unk_04;
    unsigned int unk_08;
};

class UnkType_10e80130 : public UnkType_10e80130_10e809c0
{
public:
    UnkType_10e80130(int Value);

private:
    int unk_e0;
    int unk_e4[0x20 / 4];
    UnkType_10e80130_Array unk_104;
    UnkType_10e80130_Array unk_110;
};

// UnkType_10e80130::UnkType_10e80130
UnkType_10e80130::UnkType_10e80130(int Value)
{
    Unk_10e80900();
    unk_e0 = Value;
    GUnk_111cf4d0++;
}
