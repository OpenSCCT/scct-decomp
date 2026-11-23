// campaign_leaf_57dfa0.cpp -- destructor at VA 0x10e7dfa0: frees every block in the pointer array
// at 0x04 through the allocator (second virtual method) and empties the array, whose own destructor
// then frees its storage (sixth virtual method) unless the top bit of its capacity word is set. The
// class names are invented; the addresses are the binary's.

#include "campaign_global_1131b3d8.h"

struct UnkType_10e7dfa0_Array
{
    void** unk_00;
    int unk_04;
    int unk_08;

    // UnkType_10e7dfa0_Array::Begin
    void** Begin()
    {
        return unk_00;
    }

    // UnkType_10e7dfa0_Array::End
    void** End()
    {
        return unk_00 + unk_04;
    }

    // UnkType_10e7dfa0_Array::~UnkType_10e7dfa0_Array
    // guess: frees the storage unless the top bit of the capacity word marks it as not owned.
    ~UnkType_10e7dfa0_Array()
    {
        if ( ( unk_08 & 0x80000000 ) == 0 )
        {
            GUnk_1131b3d8->VirtualSlot5(unk_00, ( unk_08 & 0x7fffffff ) * sizeof(void*), 0x12);
        }
    }
};

class UnkType_10e7dfa0
{
public:
    ~UnkType_10e7dfa0();

private:
    int unk_00;
    UnkType_10e7dfa0_Array unk_04;
};

// UnkType_10e7dfa0::~UnkType_10e7dfa0
UnkType_10e7dfa0::~UnkType_10e7dfa0()
{
    for ( void** Block = unk_04.Begin(); Block < unk_04.End(); Block++ )
    {
        GUnk_1131b3d8->VirtualSlot1(*Block);
    }
    unk_04.unk_04 = 0;
}
