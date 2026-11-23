// campaign_leaf_078150.cpp -- constructor at VA 0x10978150 taking two bit counts: clears the value
// at 0x00, stores 1 shifted left by each bit count at 0x04 and 0x08 and the bit counts in the bytes
// at 0x0c and 0x0d; constructs the member at 0x10, an object whose vtable is at VA 0x110bec68 and
// whose base class, at 0x04 of it, constructs its array member at 0x08 with the product of the two
// as its count and capacity, its data allocated through virtual slot 1 of the allocator the global
// at VA 0x111c88a0 points to, tagged "FArray::BYTE", and then clears its values at 0x00 and 0x04.
// The class and member names are invented; the offsets, the tag and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_111c88a0_078150
{
public:
    UnkType_111c88a0_078150(int Count)
    : unk_00(0)
    , unk_04(Count)
    , unk_08(Count)
    {
        unk_00 = static_cast<unsigned char*>(GUnk_111c88a0->Realloc(unk_00, unk_08,
                                                                          L"FArray::BYTE"));
    }

private:
    unsigned char* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_110bec68_078150_Base
{
public:
    UnkType_110bec68_078150_Base(int Count)
    : unk_08(Count)
    {
        unk_00 = 0;
        unk_04 = 0;
    }

private:
    int unk_00;
    int unk_04;
    UnkType_111c88a0_078150 unk_08;
};

class UnkType_110bec68 : public UnkType_110bec68_078150_Base
{
public:
    UnkType_110bec68(int Count)
    : UnkType_110bec68_078150_Base(Count)
    {
    }

    virtual ~UnkType_110bec68();
};

class UnkType_10978150
{
public:
    UnkType_10978150(unsigned char WidthBits, unsigned char HeightBits);

private:
    int unk_00;
    int unk_04;
    int unk_08;
    unsigned char unk_0c;
    unsigned char unk_0d;
    UnkType_110bec68 unk_10;
};

// UnkType_10978150::UnkType_10978150
UnkType_10978150::UnkType_10978150(unsigned char WidthBits, unsigned char HeightBits)
: unk_00(0)
, unk_04(1 << WidthBits)
, unk_08(1 << HeightBits)
, unk_0c(WidthBits)
, unk_0d(HeightBits)
, unk_10(unk_04 * unk_08)
{
}
