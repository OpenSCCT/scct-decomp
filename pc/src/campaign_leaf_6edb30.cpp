// campaign_leaf_6edb30.cpp -- destructor at VA 0x10fedb30: frees the block at 0x00 through the
// allocator at VA 0x1131b3d8, giving its size, (mask at 0x08 + 1) slots of three ints, and tag
// 0x12. The class, method and member names are invented; the offsets and addresses are the
// binary's.

#include "campaign_global_1131b3d8.h"

void Unk_10dffeb0(void* Dest, int Value, unsigned int Count);

class UnkType_10fedb30_Table
{
public:
    ~UnkType_10fedb30_Table();

private:
    int* unk_0;
    int unk_4;
    int unk_8;
};

// UnkType_10fedb30_Table::~UnkType_10fedb30_Table
UnkType_10fedb30_Table::~UnkType_10fedb30_Table()
{
    GUnk_1131b3d8->VirtualSlot5(unk_0, ( unk_8 + 1 ) * 3 * sizeof(int), 0x12);
}
