// campaign_leaf_059940.cpp -- destructor at VA 0x10959940: destroys the array member at 0x14
// (20-byte elements removed with the method at VA 0x1094bd60) then the array member at 0x8 (4-byte
// elements removed with the method at VA 0x10929170), freeing each array's data through virtual
// slot 2 of the allocator the global at VA 0x111c88a0 points to and clearing it. The class, member
// and method names are invented; the offsets, the sizes and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10929170_059940
{
public:
    ~UnkType_10929170_059940()
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

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_1094bd60_059940
{
public:
    ~UnkType_1094bd60_059940()
    {
        Unk_1094bd60(0, unk_04, 20);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_1094bd60(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10959940
{
public:
    ~UnkType_10959940();

private:
    unsigned char unk_00[0x8];
    UnkType_10929170_059940 unk_08;
    UnkType_1094bd60_059940 unk_14;
};

// UnkType_10959940::~UnkType_10959940
UnkType_10959940::~UnkType_10959940()
{
}
