// campaign_leaf_2363b0.cpp -- a member function at VA 0x10b363b0: when the byte at 0x30 is set, it
// calls its own member at VA 0x10b74b70, clears the ints at 0x34 and 0x38, empties the arrays at
// 0x40, 0x4c, 0x58 and 0x64 (each block is reallocated to no bytes through virtual slot 1 of the
// allocator the global at VA 0x111c88a0 points to, tagged L"FArray"), sets the ints at 0x70 and
// 0x74 to -1 and clears the bytes at 0x78 and 0x30. It returns true. guess: resets the object. The
// class, method and member names are invented; the offsets, addresses, string and slot are the
// binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10b363b0_Array
{
public:
    // guess: removes every element and frees the block (an inline helper; name invented)
    void Empty()
    {
        unk_04 = 0;
        unk_08 = 0;
        unk_00 = GUnk_111c88a0->Realloc(unk_00, 0, L"FArray");
    }

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10b363b0
{
public:
    void Unk_10b74b70();
    bool Unk_10b363b0();

private:
    unsigned char unk_00[0x30];
    bool unk_30;
    int unk_34;
    int unk_38;
    int unk_3c;
    UnkType_10b363b0_Array unk_40;
    UnkType_10b363b0_Array unk_4c;
    UnkType_10b363b0_Array unk_58;
    UnkType_10b363b0_Array unk_64;
    int unk_70;
    int unk_74;
    bool unk_78;
};

// UnkType_10b363b0::Unk_10b363b0
bool UnkType_10b363b0::Unk_10b363b0()
{
    if ( unk_30 )
    {
        Unk_10b74b70();
        unk_34 = 0;
        unk_38 = 0;
        unk_40.Empty();
        unk_4c.Empty();
        unk_58.Empty();
        unk_64.Empty();
        unk_70 = -1;
        unk_74 = -1;
        unk_78 = false;
        unk_30 = false;
    }
    return true;
}
