// campaign_leaf_2df1f0.cpp -- method at VA 0x10bdf1f0 of a dynamic array (data pointer, count) of
// 12-byte elements that are themselves dynamic arrays: destroys every element (removing its
// contents through the method at VA 0x10929170 with 4 as the element size, freeing its data through
// virtual slot 2 of the allocator at VA 0x111c88a0 and clearing its three words), then sets the
// count to 0. The class, member and method names are invented; the offsets and the addresses are
// the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10bdf1f0_Elem
{
public:
    ~UnkType_10bdf1f0_Elem()
    {
        Unk_10929170(0, unk_04, 4);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10929170(int Index, int Count, int ElementSize);

    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10bdf1f0
{
public:
    void Unk_10bdf1f0();

private:
    UnkType_10bdf1f0_Elem* unk_00;
    int unk_04;
};

// UnkType_10bdf1f0::Unk_10bdf1f0
void UnkType_10bdf1f0::Unk_10bdf1f0()
{
    for ( int Index = 0; Index < unk_04; Index++ )
    {
        unk_00[Index].~UnkType_10bdf1f0_Elem();
    }
    unk_04 = 0;
}
