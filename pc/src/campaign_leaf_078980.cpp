// campaign_leaf_078980.cpp -- method at VA 0x10978980: removes the elements in the range its
// arguments give (first index, count) from an array of 0x28-byte elements (data at 0x00): destroys
// the member at 0x10 of each, an object whose vtable is at VA 0x110bec68 (passes it to virtual slot
// 18, vtable offset 0x48, of the object at 0x04 of it when that is set, then destroys its array
// member at 0x0c: removes its 1-byte elements with the method at VA 0x10966210, frees its data
// through virtual slot 2 of the allocator the global at VA 0x111c88a0 points to and clears it),
// then passes the range and the element size to the method at VA 0x109779f0. The class, member and
// method names are invented; the offsets, the slots, the sizes and the addresses are the binary's.

#include "campaign_leaf_110bec68.h"

class UnkType_110bec68_078980_Item
{
private:
    unsigned char unk_00[0x10];
    UnkType_110bec68 unk_10;
};

class UnkType_10978980
{
public:
    void Unk_10978980(int Index, int Count);
    void Unk_109779f0(int Index, int Count, int ElementSize);

private:
    UnkType_110bec68_078980_Item* unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_10978980::Unk_10978980
void UnkType_10978980::Unk_10978980(int Index, int Count)
{
    for ( int i = Index; i < Index + Count; i++ )
    {
        unk_00[i].~UnkType_110bec68_078980_Item();
    }
    Unk_109779f0(Index, Count, sizeof(UnkType_110bec68_078980_Item));
}
