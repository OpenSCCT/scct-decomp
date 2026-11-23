// campaign_leaf_03a2f0.cpp -- destructor at VA 0x1093a2f0: destroys the array member at 0x18
// (12-byte elements removed with the method at VA 0x10929260) then the array member at 0x8 (4-byte
// elements removed with the method at VA 0x10929170), freeing each array's data through virtual
// slot 2 of the allocator the global at VA 0x111c88a0 points to and clearing it. The class, member
// and method names are invented; the offsets, the sizes and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10929170_03a2f0
{
public:
    ~UnkType_10929170_03a2f0()
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

class UnkType_10929260_03a2f0
{
public:
    ~UnkType_10929260_03a2f0()
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

class UnkType_1093a2f0
{
public:
    ~UnkType_1093a2f0();

private:
    unsigned char unk_00[0x8];
    UnkType_10929170_03a2f0 unk_08;
    unsigned char unk_14[0x4];
    UnkType_10929260_03a2f0 unk_18;
};

// UnkType_1093a2f0::~UnkType_1093a2f0
UnkType_1093a2f0::~UnkType_1093a2f0()
{
}
