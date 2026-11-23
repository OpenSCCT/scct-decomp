// campaign_leaf_0c6a20.cpp -- destructor at VA 0x109c6a20 of a class with two dynamic arrays (data
// pointer, count, capacity) at 0x04 and 0x10: destroys them in reverse order; each passes 0, its
// count and the element size 4 to the method at VA 0x10929170, frees its data (when set) through
// virtual slot 2 of the allocator global at VA 0x111c88a0 and zeroes its three members. The class,
// member and method names are invented; the offsets and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_109c6a20_Array
{
public:
    ~UnkType_109c6a20_Array()
    {
        Unk_10929170(0, unk_04, 4);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10929170(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109c6a20
{
public:
    ~UnkType_109c6a20();

private:
    int unk_00;
    UnkType_109c6a20_Array unk_04;
    UnkType_109c6a20_Array unk_10;
};

// UnkType_109c6a20::~UnkType_109c6a20
UnkType_109c6a20::~UnkType_109c6a20()
{
}
