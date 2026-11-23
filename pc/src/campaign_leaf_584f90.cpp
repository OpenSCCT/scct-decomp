// campaign_leaf_584f90.cpp -- destructor at VA 0x10e84f90: installs this class's vtable (VA
// 0x1114f358), calls the method at VA 0x10e84ef0, then destroys the arrays at 0x14 and 0x08 (each
// freeing its storage through the allocator unless the top bit of its capacity word is set) and the
// base part, whose inline destructor installs the vtable at VA 0x110c1d60. The class names are
// invented; the addresses are the binary's.

#include "campaign_global_1131b3d8.h"

class UnkType_10e84f90_Root
{
public:
    // UnkType_10e84f90_Root::~UnkType_10e84f90_Root
    virtual ~UnkType_10e84f90_Root()
    {
    }
};

struct UnkType_10e84f90_Array
{
    int* unk_00;
    int unk_04;
    int unk_08;

    // UnkType_10e84f90_Array::~UnkType_10e84f90_Array
    // guess: frees the storage unless the top bit of the capacity
    // word marks it as not owned.
    ~UnkType_10e84f90_Array()
    {
        if ( ( unk_08 & 0x80000000 ) == 0 )
        {
            GUnk_1131b3d8->VirtualSlot5(unk_00, ( unk_08 & 0x7fffffff ) * sizeof(int), 0x12);
        }
    }
};

class UnkType_10e84f90 : public UnkType_10e84f90_Root
{
public:
    ~UnkType_10e84f90();

    void Unk_10e84ef0();

private:
    int unk_04;
    UnkType_10e84f90_Array unk_08;
    UnkType_10e84f90_Array unk_14;
};

// UnkType_10e84f90::~UnkType_10e84f90
UnkType_10e84f90::~UnkType_10e84f90()
{
    Unk_10e84ef0();
}
