// campaign_leaf_567fa0.cpp -- destructor at VA 0x10e67fa0: destroys the arrays at 0x90, 0x34, 0x20,
// each freeing its storage through the allocator (sixth virtual method) unless the top bit of its
// capacity word is set, then runs the base class destructor at VA 0x10e6d070. The class names are
// invented; the addresses are the binary's.

#include "campaign_global_1131b3d8.h"

struct UnkType_10e67fa0_Array1
{
    char* unk_00;
    int unk_04;
    int unk_08;

    // UnkType_10e67fa0_Array1::~UnkType_10e67fa0_Array1
    // guess: frees the storage unless the top bit of the capacity word marks it as not owned.
    ~UnkType_10e67fa0_Array1()
    {
        if ( ( unk_08 & 0x80000000 ) == 0 )
        {
            GUnk_1131b3d8->VirtualSlot5(unk_00, ( unk_08 & 0x7fffffff ) * sizeof(char), 0x12);
        }
    }
};

struct UnkType_10e67fa0_Element1c
{
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
    int unk_10;
    int unk_14;
    int unk_18;
};

struct UnkType_10e67fa0_Array1c
{
    UnkType_10e67fa0_Element1c* unk_00;
    int unk_04;
    int unk_08;

    // UnkType_10e67fa0_Array1c::~UnkType_10e67fa0_Array1c
    // guess: frees the storage unless the top bit of the capacity word marks it as not owned.
    ~UnkType_10e67fa0_Array1c()
    {
        if ( ( unk_08 & 0x80000000 ) == 0 )
        {
            GUnk_1131b3d8->VirtualSlot5(
                unk_00, ( unk_08 & 0x7fffffff ) * sizeof(UnkType_10e67fa0_Element1c), 0x12);
        }
    }
};

struct UnkType_10e67fa0_Element20
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

struct UnkType_10e67fa0_Array20
{
    UnkType_10e67fa0_Element20* unk_00;
    int unk_04;
    int unk_08;

    // UnkType_10e67fa0_Array20::~UnkType_10e67fa0_Array20
    // guess: frees the storage unless the top bit of the capacity word marks it as not owned.
    ~UnkType_10e67fa0_Array20()
    {
        if ( ( unk_08 & 0x80000000 ) == 0 )
        {
            GUnk_1131b3d8->VirtualSlot5(
                unk_00, ( unk_08 & 0x7fffffff ) * sizeof(UnkType_10e67fa0_Element20), 0x12);
        }
    }
};

class UnkType_10e67fa0_10e6d070
{
public:
    ~UnkType_10e67fa0_10e6d070();

private:
    int unk_00[0x20 / 4];
};

class UnkType_10e67fa0 : public UnkType_10e67fa0_10e6d070
{
public:
    ~UnkType_10e67fa0();

private:
    UnkType_10e67fa0_Array1 unk_20;
    int unk_2c[0x8 / 4];
    UnkType_10e67fa0_Array20 unk_34;
    int unk_40[0x50 / 4];
    UnkType_10e67fa0_Array1c unk_90;
};

// UnkType_10e67fa0::~UnkType_10e67fa0
UnkType_10e67fa0::~UnkType_10e67fa0()
{
}
