// campaign_leaf_584bc0.cpp -- constructor at VA 0x10e84bc0: runs the base class constructor at VA
// 0x10e809c0, installs this class's vtable (VA 0x1114f950), calls the base method at VA 0x10e80900,
// stores its argument at 0xe0, clears the members at 0xe4-0xf4 and 0x140 and counts the instance
// in the global at VA 0x111cf4e8. The class names are invented; the addresses are the binary's.

#include "campaign_global_111cf4e8.h"

class UnkType_10e84bc0_10e809c0
{
public:
    UnkType_10e84bc0_10e809c0();

    virtual void VirtualSlot0();

    void Unk_10e80900();

private:
    int unk_04[0xdc / 4];
};

class UnkType_10e84bc0 : public UnkType_10e84bc0_10e809c0
{
public:
    UnkType_10e84bc0(int Value);

private:
    int unk_e0;
    int unk_e4;
    int unk_e8;
    int unk_ec;
    int unk_f0;
    int unk_f4;
    int unk_f8[0x48 / 4];
    int unk_140;
};

// UnkType_10e84bc0::UnkType_10e84bc0
UnkType_10e84bc0::UnkType_10e84bc0(int Value)
{
    Unk_10e80900();
    unk_e0 = Value;
    unk_e4 = 0;
    unk_e8 = 0;
    unk_ec = 0;
    unk_f0 = 0;
    unk_f4 = 0;
    unk_140 = 0;
    GUnk_111cf4e8++;
}
