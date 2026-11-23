// campaign_leaf_059d30.cpp -- destructor at VA 0x10959d30: destroys the array member at 0x1c
// (elements removed with the method at VA 0x10951d30), then the array member at 0x10 (elements
// removed with the method at VA 0x10951d30), then the array member at 0x4 (12-byte elements removed
// with the method at VA 0x10929260), freeing each array's data through virtual slot 2 of the
// allocator the global at VA 0x111c88a0 points to and clearing it. The class, member and method
// names are invented; the offsets, the sizes and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10929260_059d30
{
public:
    ~UnkType_10929260_059d30()
    {
        Unk_10929260(0, unk_04, 12);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10929260(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10951d30_059d30
{
public:
    ~UnkType_10951d30_059d30()
    {
        Unk_10951d30(0, unk_04);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10951d30(int Index, int Count);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10959d30
{
public:
    ~UnkType_10959d30();

private:
    unsigned char unk_00[0x4];
    UnkType_10929260_059d30 unk_04;
    UnkType_10951d30_059d30 unk_10;
    UnkType_10951d30_059d30 unk_1c;
};

// UnkType_10959d30::~UnkType_10959d30
UnkType_10959d30::~UnkType_10959d30()
{
}
