// campaign_leaf_2e6300.cpp -- method at VA 0x10be6300 taking a dynamic array of words by value:
// returns 1 when the word at 0xac is one of its elements and 0 otherwise, destroying the array on
// the way out (removing its contents through the method at VA 0x10929b20 with 4 as the element
// size and freeing its data through virtual slot 2 of the allocator at VA 0x111c88a0). The class,
// member and method names are invented; the offsets and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10be6300_Array
{
public:
    ~UnkType_10be6300_Array()
    {
        Unk_10929b20(0, unk_04, 4);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10929b20(int Index, int Count, int ElementSize);

    int* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10be6300
{
public:
    int Unk_10be6300(UnkType_10be6300_Array List);

private:
    unsigned char unk_00[0xac];
    int unk_ac;
};

// UnkType_10be6300::Unk_10be6300
int UnkType_10be6300::Unk_10be6300(UnkType_10be6300_Array List)
{
    for ( int Index = 0; Index < List.unk_04; Index++ )
    {
        if ( unk_ac == List.unk_00[Index] )
        {
            return 1;
        }
    }
    return 0;
}
