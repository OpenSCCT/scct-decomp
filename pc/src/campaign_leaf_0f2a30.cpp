// campaign_leaf_0f2a30.cpp -- method at VA 0x109f2a30 of a dynamic array of 0x30-byte records (data
// pointer at 0x00, count at 0x04) taking one argument it does not read: destroys every record (the
// dynamic array at 0x18 of each: method at VA 0x10907710 with 0, its count and the element size 2,
// then frees its data), zeroes the count and frees the data, all through virtual slot 2 of the
// allocator global at VA 0x111c88a0. guess: an instance of the engine's TArray<T>::Empty. The
// class, member and method names are invented; the offsets and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_109f2a30_Array
{
public:
    ~UnkType_109f2a30_Array()
    {
        Unk_10907710(0, unk_04, 2);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10907710(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

struct UnkType_109f2a30_Record
{
    unsigned char unk_00[0x18];
    UnkType_109f2a30_Array unk_18;
    unsigned char unk_24[0x30 - 0x24];
};

class UnkType_109f2a30
{
public:
    void Unk_109f2a30(int Slack);

private:
    UnkType_109f2a30_Record* unk_00;
    int unk_04;
};

// UnkType_109f2a30::Unk_109f2a30
void UnkType_109f2a30::Unk_109f2a30(int)
{
    for ( int i = 0; i < unk_04; i++ )
    {
        unk_00[i].~UnkType_109f2a30_Record();
    }
    unk_04 = 0;
    if ( unk_00 )
    {
        GUnk_111c88a0->Free(unk_00);
    }
    unk_00 = 0;
}
