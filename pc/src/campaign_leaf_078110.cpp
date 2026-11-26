// campaign_leaf_078110.cpp -- constructor at VA 0x10978110: constructs the member at 0x10, an
// object whose vtable is at VA 0x110bec68: clears its values at 0x04 and 0x08 and constructs its
// array member at 0x0c cleared, with its data allocated for its capacity of 0 through virtual slot
// 1 of the allocator the global at VA 0x111c88a0 points to, tagged "FArray::BYTE". The class and
// member names are invented; the offsets, the tag and the addresses are the binary's.

#include "campaign_leaf_110bec68.h"

class UnkType_10978110
{
public:
    UnkType_10978110();

private:
    unsigned char unk_00[0x10];
    UnkType_110bec68 unk_10;
};

// UnkType_10978110::UnkType_10978110
UnkType_10978110::UnkType_10978110()
{
}
