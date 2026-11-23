// campaign_leaf_59a430.cpp -- destructor at VA 0x10e9a430: destroys the arrays at 0x58, 0x4c, 0x40,
// 0x34, 0x28, 0x1c, 0x10, 0x04, each freeing its storage through the allocator (sixth virtual
// method) unless the top bit of its capacity word is set. The class names are invented; the
// addresses are the binary's.

#include "campaign_global_1131b3d8.h"

struct UnkType_10e9a430_Array4
{
    int* unk_00;
    int unk_04;
    int unk_08;

    // UnkType_10e9a430_Array4::~UnkType_10e9a430_Array4
    // guess: frees the storage unless the top bit of the capacity word marks it as not owned.
    ~UnkType_10e9a430_Array4()
    {
        if ( ( unk_08 & 0x80000000 ) == 0 )
        {
            GUnk_1131b3d8->VirtualSlot5(unk_00, ( unk_08 & 0x7fffffff ) * sizeof(int), 0x12);
        }
    }
};

class UnkType_10e9a430
{
public:
    ~UnkType_10e9a430();

private:
    int unk_00[0x4 / 4];
    UnkType_10e9a430_Array4 unk_04;
    UnkType_10e9a430_Array4 unk_10;
    UnkType_10e9a430_Array4 unk_1c;
    UnkType_10e9a430_Array4 unk_28;
    UnkType_10e9a430_Array4 unk_34;
    UnkType_10e9a430_Array4 unk_40;
    UnkType_10e9a430_Array4 unk_4c;
    UnkType_10e9a430_Array4 unk_58;
};

// UnkType_10e9a430::~UnkType_10e9a430
UnkType_10e9a430::~UnkType_10e9a430()
{
}
