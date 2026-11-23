// campaign_leaf_0abbc0.cpp -- method at VA 0x109abbc0: empties each of the four rows of three
// 0x38-byte records at 0xb8, whose first member is a dynamic array of wide characters (data
// pointer, count, capacity): zeroes the count and the capacity and reallocates the data to nothing
// through virtual slot 1 of the allocator global at VA 0x111c88a0 with the tag "FArray::_WORD". The
// class, member and method names are invented; the offsets and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_109abbc0_String
{
public:

    void Realloc()
    {
        unk_00 = (unsigned short*)GUnk_111c88a0->Realloc(
            unk_00, unk_08 * sizeof(unsigned short), L"FArray::_WORD");
    }

    void Empty()
    {
        unk_04 = 0;
        unk_08 = 0;
        Realloc();
    }

private:
    unsigned short* unk_00;
    int unk_04;
    int unk_08;
};

struct UnkType_109abbc0_Record
{
    UnkType_109abbc0_String unk_00;
    unsigned char unk_0c[0x38 - 0x0c];
};

class UnkType_109abbc0
{
public:
    void Unk_109abbc0();

private:
    unsigned char unk_00[0xb8];
    UnkType_109abbc0_Record unk_b8[4][3];
};

// UnkType_109abbc0::Unk_109abbc0
void UnkType_109abbc0::Unk_109abbc0()
{
    for ( int i = 0; i < 4; i++ )
    {
        for ( int j = 0; j < 3; j++ )
        {
            unk_b8[i][j].unk_00.Empty();
        }
    }
}
