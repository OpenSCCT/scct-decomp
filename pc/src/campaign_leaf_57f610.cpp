// campaign_leaf_57f610.cpp -- constructor at VA 0x10e7f610: runs the base class constructor at VA
// 0x10e809c0, installs this class's vtable (VA 0x1114ef3c), constructs the empty array at 0xe4,
// calls the base method at VA 0x10e80900, stores its argument at 0xe0, counts the instance in the
// global at VA 0x111cf4cc and clears the member at 0xf0. The class names are invented; the
// addresses are the binary's.

#include "campaign_global_111cf4cc.h"

class UnkType_10e7f610_10e809c0
{
public:
    UnkType_10e7f610_10e809c0();

    virtual void VirtualSlot0();

    void Unk_10e80900();

private:
    int unk_04[0xdc / 4];
};

struct UnkType_10e7f610_Array
{
    // UnkType_10e7f610_Array::UnkType_10e7f610_Array
    UnkType_10e7f610_Array()
        : unk_00(0), unk_04(0), unk_08(0x80000000)
    {
    }

    void* unk_00;
    int unk_04;
    unsigned int unk_08;
};

class UnkType_10e7f610 : public UnkType_10e7f610_10e809c0
{
public:
    UnkType_10e7f610(int Value);

private:
    int unk_e0;
    UnkType_10e7f610_Array unk_e4;
    int unk_f0;
};

// UnkType_10e7f610::UnkType_10e7f610
UnkType_10e7f610::UnkType_10e7f610(int Value)
{
    Unk_10e80900();
    unk_e0 = Value;
    GUnk_111cf4cc++;
    unk_f0 = 0;
}
