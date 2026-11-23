// campaign_leaf_5999f0.cpp -- destructor at VA 0x10e999f0: destroys the arrays at 0x18, 0x0c, 0x00,
// each freeing its storage through the allocator (sixth virtual method) unless the top bit of its
// capacity word is set. The class names are invented; the addresses are the binary's.

#include "campaign_global_1131b3d8.h"

struct UnkType_10e999f0_Array4
{
    int* unk_00;
    int unk_04;
    int unk_08;

    // UnkType_10e999f0_Array4::~UnkType_10e999f0_Array4
    // guess: frees the storage unless the top bit of the capacity word marks it as not owned.
    ~UnkType_10e999f0_Array4()
    {
        if ( ( unk_08 & 0x80000000 ) == 0 )
        {
            GUnk_1131b3d8->VirtualSlot5(unk_00, ( unk_08 & 0x7fffffff ) * sizeof(int), 0x12);
        }
    }
};

struct UnkType_10e999f0_Element16
{
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
};

struct UnkType_10e999f0_Array16
{
    UnkType_10e999f0_Element16* unk_00;
    int unk_04;
    int unk_08;

    // UnkType_10e999f0_Array16::~UnkType_10e999f0_Array16
    // guess: frees the storage unless the top bit of the capacity word marks it as not owned.
    ~UnkType_10e999f0_Array16()
    {
        if ( ( unk_08 & 0x80000000 ) == 0 )
        {
            GUnk_1131b3d8->VirtualSlot5(
                unk_00, ( unk_08 & 0x7fffffff ) * sizeof(UnkType_10e999f0_Element16), 0x12);
        }
    }
};

class UnkType_10e999f0
{
public:
    ~UnkType_10e999f0();

private:
    UnkType_10e999f0_Array16 unk_00;
    UnkType_10e999f0_Array16 unk_0c;
    UnkType_10e999f0_Array4 unk_18;
};

// UnkType_10e999f0::~UnkType_10e999f0
UnkType_10e999f0::~UnkType_10e999f0()
{
}
