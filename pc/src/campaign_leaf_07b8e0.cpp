// campaign_leaf_07b8e0.cpp -- method at VA 0x1097b8e0: empties an array of 12-byte elements (data
// at 0x00, count at 0x04, capacity at 0x08), each itself an array: destroys each element (removes
// its 4-byte elements with the method at VA 0x10919a00, frees its data through virtual slot 2 of
// the allocator the global at VA 0x111c88a0 points to and clears it), sets the count to 0 and the
// capacity to its argument, and passes the element size to the method at VA 0x10976350. The class,
// member and method names are invented; the offsets, the sizes and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10919a00_07b8e0
{
public:
    ~UnkType_10919a00_07b8e0()
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

class UnkType_1097b8e0
{
public:
    void Unk_1097b8e0(int Slack);
    void Unk_10976350(int ElementSize);

private:
    UnkType_10919a00_07b8e0* unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_1097b8e0::Unk_1097b8e0
void UnkType_1097b8e0::Unk_1097b8e0(int Slack)
{
    for ( int i = 0; i < unk_04; i++ )
    {
        unk_00[i].~UnkType_10919a00_07b8e0();
    }
    unk_04 = 0;
    unk_08 = Slack;
    Unk_10976350(sizeof(UnkType_10919a00_07b8e0));
}
