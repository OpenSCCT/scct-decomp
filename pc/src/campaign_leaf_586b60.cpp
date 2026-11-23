// campaign_leaf_586b60.cpp -- constructor at VA 0x10e86b60: runs the base class constructor at VA
// 0x10e809c0, installs this class's vtable (VA 0x1114fba8), constructs the empty array at 0xe4,
// calls the base method at VA 0x10e80900, stores its argument at 0xe0, counts the instance in the
// global at VA 0x111cf4fc, clears the members at 0xf0-0xf5, passes the global object at VA
// 0x111cf450 to the method at VA 0x10ab7680 of the member at 0x100 and clears the member at 0x140.
// The class names are invented; the addresses are the binary's.

#include "campaign_global_111cf450.h"
#include "campaign_global_111cf4fc.h"

class UnkType_10e86b60_10e809c0
{
public:
    UnkType_10e86b60_10e809c0();

    virtual void VirtualSlot0();

    void Unk_10e80900();

private:
    int unk_04[0xdc / 4];
};

struct UnkType_10e86b60_Array
{
    // UnkType_10e86b60_Array::UnkType_10e86b60_Array
    UnkType_10e86b60_Array()
        : unk_00(0), unk_04(0), unk_08(0x80000000)
    {
    }

    void* unk_00;
    int unk_04;
    unsigned int unk_08;
};

class UnkType_10e86b60_100
{
public:
    void Unk_10ab7680(const UnkType_111cf450& Other);

private:
    int unk_00[0x40 / 4];
};

class UnkType_10e86b60 : public UnkType_10e86b60_10e809c0
{
public:
    UnkType_10e86b60(int Value);

private:
    int unk_e0;
    UnkType_10e86b60_Array unk_e4;
    int unk_f0;
    char unk_f4;
    char unk_f5;
    char unk_f6[2];
    int unk_f8[2];
    UnkType_10e86b60_100 unk_100;
    int unk_140;
};

// UnkType_10e86b60::UnkType_10e86b60
UnkType_10e86b60::UnkType_10e86b60(int Value)
{
    Unk_10e80900();
    unk_e0 = Value;
    GUnk_111cf4fc++;
    unk_f0 = 0;
    unk_f4 = 0;
    unk_f5 = 0;
    unk_100.Unk_10ab7680(GUnk_111cf450);
    unk_140 = 0;
}
