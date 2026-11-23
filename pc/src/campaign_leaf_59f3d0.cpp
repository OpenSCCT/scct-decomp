// campaign_leaf_59f3d0.cpp -- destructor at VA 0x10e9f3d0: destroys the arrays at 0x5c, 0x50, 0x44,
// each freeing its storage through the allocator (sixth virtual method) unless the top bit of its
// capacity word is set, then runs the base class destructor at VA 0x10e9f270. The class names are
// invented; the addresses are the binary's.

#include "campaign_global_1131b3d8.h"

struct UnkType_10e9f3d0_Array4
{
    int* unk_00;
    int unk_04;
    int unk_08;

    // UnkType_10e9f3d0_Array4::~UnkType_10e9f3d0_Array4
    // guess: frees the storage unless the top bit of the capacity word marks it as not owned.
    ~UnkType_10e9f3d0_Array4()
    {
        if ( ( unk_08 & 0x80000000 ) == 0 )
        {
            GUnk_1131b3d8->VirtualSlot5(unk_00, ( unk_08 & 0x7fffffff ) * sizeof(int), 0x12);
        }
    }
};

class UnkType_10e9f3d0_10e9f270
{
public:
    ~UnkType_10e9f3d0_10e9f270();

private:
    int unk_00[0x44 / 4];
};

class UnkType_10e9f3d0 : public UnkType_10e9f3d0_10e9f270
{
public:
    ~UnkType_10e9f3d0();

private:
    UnkType_10e9f3d0_Array4 unk_44;
    UnkType_10e9f3d0_Array4 unk_50;
    UnkType_10e9f3d0_Array4 unk_5c;
};

// UnkType_10e9f3d0::~UnkType_10e9f3d0
UnkType_10e9f3d0::~UnkType_10e9f3d0()
{
}
