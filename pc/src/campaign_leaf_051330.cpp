// campaign_leaf_051330.cpp -- destructor at VA 0x10951330: destroys the array member at 0x8c and
// then the one at 0x80 (4-byte elements removed with the method at VA 0x10929170), freeing each
// array's data through virtual slot 2 of the allocator the global at VA 0x111c88a0 points to and
// clearing it. The class, member and method names are invented; the offsets, the size and the
// addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10929170_051330
{
public:
    ~UnkType_10929170_051330()
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

class UnkType_10951330
{
public:
    ~UnkType_10951330();

private:
    unsigned char unk_00[0x80];
    UnkType_10929170_051330 unk_80;
    UnkType_10929170_051330 unk_8c;
};

// UnkType_10951330::~UnkType_10951330
UnkType_10951330::~UnkType_10951330()
{
}
