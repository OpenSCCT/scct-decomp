// campaign_leaf_584ef0.cpp -- thiscall method at VA 0x10e84ef0: for every entry, frees the
// matching entry of the array at 0x14 through the allocator's second virtual method and calls the
// method at VA 0x10e07450 on the matching entry of the array at 0x08, then empties both arrays,
// freeing their storage (allocator tag 0x12) unless the top bit of the capacity word marks it as
// not owned. The companion of VA 0x10e84e00. All names are invented; the addresses are the
// binary's.

#include "campaign_global_1131b3d8.h"

class UnkType_10e84ef0_Entry
{
public:
    void Unk_10e07450();
};

template<class T> struct UnkType_10e84ef0_Array
{
    T* unk_00;
    int unk_04;
    int unk_08;

    // UnkType_10e84ef0_Array::Empty
    // guess: frees owned storage and leaves the array empty, owning nothing.
    void Empty()
    {
        if ( ( unk_08 & 0x80000000 ) == 0 )
        {
            GUnk_1131b3d8->VirtualSlot5(unk_00, ( unk_08 & 0x7fffffff ) * sizeof(T), 0x12);
        }
        unk_00 = 0;
        unk_04 = 0;
        unk_08 = 0x80000000;
    }
};

class UnkType_10e84ef0
{
public:
    void Unk_10e84ef0();

private:
    int unk_00;
    int unk_04;
    UnkType_10e84ef0_Array<UnkType_10e84ef0_Entry*> unk_08;
    UnkType_10e84ef0_Array<void*> unk_14;
};

// UnkType_10e84ef0::Unk_10e84ef0
void UnkType_10e84ef0::Unk_10e84ef0()
{
    int Count = unk_08.unk_04;

    for ( int Index = 0; Index < Count; Index++ )
    {
        GUnk_1131b3d8->VirtualSlot1(unk_14.unk_00[Index]);
        unk_08.unk_00[Index]->Unk_10e07450();
    }
    unk_14.Empty();
    unk_08.Empty();
}
