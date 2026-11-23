// campaign_leaf_54e030.cpp -- destructor at VA 0x10e4e030: destroys the arrays at 0x2100, 0x1b0,
// 0x08, each freeing its storage through the allocator (sixth virtual method) unless the top bit of
// its capacity word is set. The class names are invented; the addresses are the binary's.

#include "campaign_global_1131b3d8.h"

struct UnkType_10e4e030_Array4
{
    int* unk_00;
    int unk_04;
    int unk_08;

    // UnkType_10e4e030_Array4::~UnkType_10e4e030_Array4
    // guess: frees the storage unless the top bit of the capacity word marks it as not owned.
    ~UnkType_10e4e030_Array4()
    {
        if ( ( unk_08 & 0x80000000 ) == 0 )
        {
            GUnk_1131b3d8->VirtualSlot5(unk_00, ( unk_08 & 0x7fffffff ) * sizeof(int), 0x12);
        }
    }
};

struct UnkType_10e4e030_Element20
{
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1c;
};

struct UnkType_10e4e030_Array20
{
    UnkType_10e4e030_Element20* unk_00;
    int unk_04;
    int unk_08;

    // UnkType_10e4e030_Array20::~UnkType_10e4e030_Array20
    // guess: frees the storage unless the top bit of the capacity word marks it as not owned.
    ~UnkType_10e4e030_Array20()
    {
        if ( ( unk_08 & 0x80000000 ) == 0 )
        {
            GUnk_1131b3d8->VirtualSlot5(
                unk_00, ( unk_08 & 0x7fffffff ) * sizeof(UnkType_10e4e030_Element20), 0x12);
        }
    }
};

struct UnkType_10e4e030_Element50
{
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1c;
    int unk_20;
    int unk_24;
    int unk_28;
    int unk_2c;
    int unk_30;
    int unk_34;
    int unk_38;
    int unk_3c;
    int unk_40;
    int unk_44;
    int unk_48;
    int unk_4c;
};

struct UnkType_10e4e030_Array50
{
    UnkType_10e4e030_Element50* unk_00;
    int unk_04;
    int unk_08;

    // UnkType_10e4e030_Array50::~UnkType_10e4e030_Array50
    // guess: frees the storage unless the top bit of the capacity word marks it as not owned.
    ~UnkType_10e4e030_Array50()
    {
        if ( ( unk_08 & 0x80000000 ) == 0 )
        {
            GUnk_1131b3d8->VirtualSlot5(
                unk_00, ( unk_08 & 0x7fffffff ) * sizeof(UnkType_10e4e030_Element50), 0x12);
        }
    }
};

class UnkType_10e4e030
{
public:
    ~UnkType_10e4e030();

private:
    int unk_00[0x8 / 4];
    UnkType_10e4e030_Array4 unk_08;
    int unk_14[0x19c / 4];
    UnkType_10e4e030_Array50 unk_1b0;
    int unk_1bc[0x1f44 / 4];
    UnkType_10e4e030_Array20 unk_2100;
};

// UnkType_10e4e030::~UnkType_10e4e030
UnkType_10e4e030::~UnkType_10e4e030()
{
}
