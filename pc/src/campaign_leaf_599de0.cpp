// campaign_leaf_599de0.cpp -- destructor at VA 0x10e99de0: destroys the arrays at 0x20, 0x10, 0x04,
// each freeing its storage through the allocator (sixth virtual method) unless the top bit of its
// capacity word is set. The class names are invented; the addresses are the binary's.

#include "campaign_global_1131b3d8.h"

struct UnkType_10e99de0_Array1
{
    char* unk_00;
    int unk_04;
    int unk_08;

    // UnkType_10e99de0_Array1::~UnkType_10e99de0_Array1
    // guess: frees the storage unless the top bit of the capacity word marks it as not owned.
    ~UnkType_10e99de0_Array1()
    {
        if ( ( unk_08 & 0x80000000 ) == 0 )
        {
            GUnk_1131b3d8->VirtualSlot5(unk_00, ( unk_08 & 0x7fffffff ) * sizeof(char), 0x12);
        }
    }
};

struct UnkType_10e99de0_Array4
{
    int* unk_00;
    int unk_04;
    int unk_08;

    // UnkType_10e99de0_Array4::~UnkType_10e99de0_Array4
    // guess: frees the storage unless the top bit of the capacity word marks it as not owned.
    ~UnkType_10e99de0_Array4()
    {
        if ( ( unk_08 & 0x80000000 ) == 0 )
        {
            GUnk_1131b3d8->VirtualSlot5(unk_00, ( unk_08 & 0x7fffffff ) * sizeof(int), 0x12);
        }
    }
};

class UnkType_10e99de0
{
public:
    ~UnkType_10e99de0();

private:
    int unk_00[0x4 / 4];
    UnkType_10e99de0_Array4 unk_04;
    UnkType_10e99de0_Array4 unk_10;
    int unk_1c[0x4 / 4];
    UnkType_10e99de0_Array1 unk_20;
};

// UnkType_10e99de0::~UnkType_10e99de0
UnkType_10e99de0::~UnkType_10e99de0()
{
}
