// campaign_leaf_078750.cpp -- method at VA 0x10978750: removes the elements in the range its
// arguments give (first index, count) from an array of 12-byte elements (data at 0x00), each
// itself an array: destroys each (removes its 4-byte elements with the method at VA 0x10919a00,
// frees its data through virtual slot 2 of the allocator the global at VA 0x111c88a0 points to
// and clears it), then passes the range and the element size to the method at VA 0x109775b0. The
// class, member and method names are invented; the offsets, the sizes and the addresses are the
// binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10919a00_078750
{
public:
    ~UnkType_10919a00_078750()
    {
        Unk_10919a00(0, unk_04, 4);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10919a00(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10978750
{
public:
    void Unk_10978750(int Index, int Count);
    void Unk_109775b0(int Index, int Count, int ElementSize);

private:
    UnkType_10919a00_078750* unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_10978750::Unk_10978750
void UnkType_10978750::Unk_10978750(int Index, int Count)
{
    for ( int i = Index; i < Index + Count; i++ )
    {
        unk_00[i].~UnkType_10919a00_078750();
    }
    Unk_109775b0(Index, Count, sizeof(UnkType_10919a00_078750));
}
