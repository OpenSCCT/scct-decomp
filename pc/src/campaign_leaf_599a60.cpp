// campaign_leaf_599a60.cpp -- destructor at VA 0x10e99a60: destroys the arrays at 0x3c, 0x30, 0x24,
// each freeing its storage through the allocator (sixth virtual method) unless the top bit of its
// capacity word is set, then runs the base class destructor at VA 0x10e999f0. The class names are
// invented; the addresses are the binary's.

#include "campaign_global_1131b3d8.h"

struct UnkType_10e99a60_Array4
{
    int* unk_00;
    int unk_04;
    int unk_08;

    // UnkType_10e99a60_Array4::~UnkType_10e99a60_Array4
    // guess: frees the storage unless the top bit of the capacity word marks it as not owned.
    ~UnkType_10e99a60_Array4()
    {
        if ( ( unk_08 & 0x80000000 ) == 0 )
        {
            GUnk_1131b3d8->VirtualSlot5(unk_00, ( unk_08 & 0x7fffffff ) * sizeof(int), 0x12);
        }
    }
};

class UnkType_10e99a60_10e999f0
{
public:
    ~UnkType_10e99a60_10e999f0();

private:
    int unk_00[0x24 / 4];
};

class UnkType_10e99a60 : public UnkType_10e99a60_10e999f0
{
public:
    ~UnkType_10e99a60();

private:
    UnkType_10e99a60_Array4 unk_24;
    UnkType_10e99a60_Array4 unk_30;
    UnkType_10e99a60_Array4 unk_3c;
};

// UnkType_10e99a60::~UnkType_10e99a60
UnkType_10e99a60::~UnkType_10e99a60()
{
}
