// campaign_leaf_57eeb0.cpp -- destructor at VA 0x10e7eeb0: installs this class's vtable (VA
// 0x1114ef14); for every 8-byte entry of the array at 0x08 deletes the entry's object and clears
// the pointer its second word points to; then destroys the array (storage freed through the
// allocator unless the top bit of its capacity word is set) and the base part, whose inline
// destructor installs the vtable at VA 0x110c1d60. The class names are invented; the addresses are
// the binary's.

#include "campaign_global_1131b3d8.h"

class UnkType_10e7eeb0_Root
{
public:
    // UnkType_10e7eeb0_Root::~UnkType_10e7eeb0_Root
    virtual ~UnkType_10e7eeb0_Root()
    {
    }
};

class UnkType_10e7eeb0_Object
{
public:
    virtual ~UnkType_10e7eeb0_Object();
};

struct UnkType_10e7eeb0_Entry
{
    UnkType_10e7eeb0_Object* unk_00;
    UnkType_10e7eeb0_Object** unk_04;
};

struct UnkType_10e7eeb0_Array
{
    UnkType_10e7eeb0_Entry* unk_00;
    int unk_04;
    int unk_08;

    // UnkType_10e7eeb0_Array::~UnkType_10e7eeb0_Array
    // guess: frees the storage unless the top bit of the capacity
    // word marks it as not owned.
    ~UnkType_10e7eeb0_Array()
    {
        if ( ( unk_08 & 0x80000000 ) == 0 )
        {
            GUnk_1131b3d8->VirtualSlot5(
                unk_00, ( unk_08 & 0x7fffffff ) * sizeof(UnkType_10e7eeb0_Entry), 0x12);
        }
    }
};

class UnkType_10e7eeb0 : public UnkType_10e7eeb0_Root
{
public:
    ~UnkType_10e7eeb0();

private:
    int unk_04;
    UnkType_10e7eeb0_Array unk_08;
};

// UnkType_10e7eeb0::~UnkType_10e7eeb0
UnkType_10e7eeb0::~UnkType_10e7eeb0()
{
    for ( int Index = 0; Index < unk_08.unk_04; Index++ )
    {
        delete unk_08.unk_00[Index].unk_00;
        *unk_08.unk_00[Index].unk_04 = 0;
    }
}
