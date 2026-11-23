// campaign_leaf_6edaf0.cpp -- constructor at VA 0x10fedaf0: allocates a block of 0xc0 bytes
// (16 slots of three ints) with tag 0x12 from the allocator at VA 0x1131b3d8, fills its first
// 0x40 bytes with 0xff through the function at VA 0x10dffeb0, clears the count at 0x04 and stores
// the slot mask 0xf at 0x08. The class, method and member names are invented; the offsets,
// sizes and addresses are the binary's.

#include "campaign_global_1131b3d8.h"

void Unk_10dffeb0(void* Dest, int Value, unsigned int Count);

class UnkType_10fedaf0_Table
{
public:
    UnkType_10fedaf0_Table();

private:
    int* unk_0;
    int unk_4;
    int unk_8;
};

// UnkType_10fedaf0_Table::UnkType_10fedaf0_Table
UnkType_10fedaf0_Table::UnkType_10fedaf0_Table()
{
    unk_0 = (int*)GUnk_1131b3d8->VirtualSlot4(0xc0, 0x12);
    Unk_10dffeb0(unk_0, 0xff, 0x40);
    unk_4 = 0;
    unk_8 = 0xf;
}
