// campaign_leaf_5a02b0.cpp -- destructor at VA 0x10ea02b0: destroys the arrays at 0x40, 0x34, 0x28,
// each freeing its storage through the allocator (sixth virtual method) unless the top bit of its
// capacity word is set, then runs the base class destructor at VA 0x10ea0110. The class names are
// invented; the addresses are the binary's.

#include "campaign_global_1131b3d8.h"

struct UnkType_10ea02b0_Array1
{
    char* unk_00;
    int unk_04;
    int unk_08;

    // UnkType_10ea02b0_Array1::~UnkType_10ea02b0_Array1
    // guess: frees the storage unless the top bit of the capacity word marks it as not owned.
    ~UnkType_10ea02b0_Array1()
    {
        if ( ( unk_08 & 0x80000000 ) == 0 )
        {
            GUnk_1131b3d8->VirtualSlot5(unk_00, ( unk_08 & 0x7fffffff ) * sizeof(char), 0x12);
        }
    }
};

struct UnkType_10ea02b0_Array4
{
    int* unk_00;
    int unk_04;
    int unk_08;

    // UnkType_10ea02b0_Array4::~UnkType_10ea02b0_Array4
    // guess: frees the storage unless the top bit of the capacity word marks it as not owned.
    ~UnkType_10ea02b0_Array4()
    {
        if ( ( unk_08 & 0x80000000 ) == 0 )
        {
            GUnk_1131b3d8->VirtualSlot5(unk_00, ( unk_08 & 0x7fffffff ) * sizeof(int), 0x12);
        }
    }
};

class UnkType_10ea02b0_10ea0110
{
public:
    ~UnkType_10ea02b0_10ea0110();

private:
    int unk_00[0x28 / 4];
};

class UnkType_10ea02b0 : public UnkType_10ea02b0_10ea0110
{
public:
    ~UnkType_10ea02b0();

private:
    UnkType_10ea02b0_Array4 unk_28;
    UnkType_10ea02b0_Array4 unk_34;
    UnkType_10ea02b0_Array1 unk_40;
};

// UnkType_10ea02b0::~UnkType_10ea02b0
UnkType_10ea02b0::~UnkType_10ea02b0()
{
}
