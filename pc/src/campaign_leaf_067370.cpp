// campaign_leaf_067370.cpp -- constructor at VA 0x10967370 taking two bit counts and a count:
// clears the value at 0x00, stores 1 shifted left by each bit count at 0x04 and 0x08 and the bit
// counts in the bytes at 0x0c and 0x0d; constructs the member at 0x10, an object whose vtable is at
// VA 0x110bec68 and whose base class, at 0x04 of it, constructs its array member at 0x08 with its
// third argument as its count and capacity, its data allocated through virtual slot 1 of the
// allocator the global at VA 0x111c88a0 points to, tagged "FArray::BYTE", and then clears its
// values at 0x00 and 0x04. The class and member names are invented; the offsets, the tag and the
// addresses are the binary's.

#include "campaign_leaf_110bec68.h"

class UnkType_10967370
{
public:
    UnkType_10967370(unsigned char WidthBits, unsigned char HeightBits, int Count);

private:
    int unk_00;
    int unk_04;
    int unk_08;
    unsigned char unk_0c;
    unsigned char unk_0d;
    UnkType_110bec68 unk_10;
};

// UnkType_10967370::UnkType_10967370
UnkType_10967370::UnkType_10967370(unsigned char WidthBits, unsigned char HeightBits, int Count)
: unk_00(0)
, unk_04(1 << WidthBits)
, unk_08(1 << HeightBits)
, unk_0c(WidthBits)
, unk_0d(HeightBits)
, unk_10(Count)
{
}
