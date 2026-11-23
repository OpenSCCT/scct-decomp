// campaign_leaf_25e970.cpp -- a member function at VA 0x10b5e970 of an array of 0x14-byte elements
// taking an index and a count: it destroys each element in that range (the element's array at 0x08
// removes all its 4-byte items with the member at VA 0x10929170, frees its block through virtual
// slot 2 of the allocator the global at VA 0x111c88a0 points to and is cleared), then passes the
// index, the count and the element size to the member at VA 0x10b5e610. guess: removes elements
// from the array. The class, method and member names are invented; the offsets, sizes, addresses
// and slot are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10b5e970_Items
{
public:
    void Unk_10929170(int Index, int Count, int Size);

    // guess: removes the items and frees the block (an inline destructor)
    ~UnkType_10b5e970_Items()
    {
        Unk_10929170(0, unk_04, 4);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_08 = 0;
        unk_04 = 0;
    }

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10b5e970_Element
{
private:
    int unk_00;
    int unk_04;
    UnkType_10b5e970_Items unk_08;
};

class UnkType_10b5e970
{
public:
    void Unk_10b5e610(int Index, int Count, int Size);
    void Unk_10b5e970(int Index, int Count);

private:
    UnkType_10b5e970_Element* unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_10b5e970::Unk_10b5e970
void UnkType_10b5e970::Unk_10b5e970(int Index, int Count)
{
    for ( int i = Index; i < Index + Count; i++ )
    {
        ( &unk_00[i] )->~UnkType_10b5e970_Element();
    }
    Unk_10b5e610(Index, Count, sizeof(UnkType_10b5e970_Element));
}
