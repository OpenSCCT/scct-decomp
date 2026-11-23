// campaign_leaf_08cac0.cpp -- destructor at VA 0x1098cac0 of a 0x40-byte class: destroys the array
// members at 0x34 and 0x28 (elements removed with the method at VA 0x1098c800, data freed through
// virtual slot 2 of the allocator the global at VA 0x111c88a0 points to), then the 12-byte member
// at 0x00 with its destructor at VA 0x1090ba70. The class, member and method names are invented;
// the offsets and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_1090ba70
{
public:
    ~UnkType_1090ba70();

private:
    int unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_1098c800_08cac0
{
public:
    ~UnkType_1098c800_08cac0()
    {
        Unk_1098c800(0, unk_04);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_1098c800(int Index, int Count);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_1098cac0
{
public:
    ~UnkType_1098cac0();

private:
    UnkType_1090ba70 unk_00;
    unsigned char unk_0c[0x1c];
    UnkType_1098c800_08cac0 unk_28;
    UnkType_1098c800_08cac0 unk_34;
};

// UnkType_1098cac0::~UnkType_1098cac0
UnkType_1098cac0::~UnkType_1098cac0()
{
}
