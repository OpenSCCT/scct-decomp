// campaign_leaf_26b330.cpp -- a member function at VA 0x10b6b330: when the byte at 0x14 is set, it
// passes the pointer at 0x1c to the free function at VA 0x10b71ee0, empties the array at 0x28 (its
// block is reallocated to no bytes through virtual slot 1 of the allocator the global at VA
// 0x111c88a0 points to, tagged L"FArray::INT"), stores 30.0 in the float at 0x4c, passes 0 to the
// member at VA 0x1090d670 of the member at 0x54, and clears the ints at 0x40 to 0x48 and 0x3c, the
// bytes at 0x15 and 0x52 to 0x50, the ints at 0x10, 0x24, 0x1c and 0x18 and the byte at 0x14. It
// returns true. guess: resets the object. The class, method and member names are invented; the
// offsets, addresses, string, constant and slot are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10b6b330_Target;

void __cdecl Unk_10b71ee0(UnkType_10b6b330_Target* Target);

class UnkType_10b6b330_Array
{
public:
    // guess: removes every element and frees the block (an inline helper; name invented)
    void Empty()
    {
        unk_04 = 0;
        unk_08 = 0;
        unk_00 = GUnk_111c88a0->Realloc(unk_00, 0, L"FArray::INT");
    }

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10b6b330_List
{
public:
    void Unk_1090d670(int Slack);

private:
    int unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10b6b330
{
public:
    bool Unk_10b6b330();

private:
    unsigned char unk_00[0x10];
    int unk_10;
    bool unk_14;
    bool unk_15;
    int unk_18;
    UnkType_10b6b330_Target* unk_1c;
    int unk_20;
    int unk_24;
    UnkType_10b6b330_Array unk_28;
    int unk_34;
    int unk_38;
    int unk_3c;
    int unk_40;
    int unk_44;
    int unk_48;
    float unk_4c;
    bool unk_50;
    bool unk_51;
    bool unk_52;
    UnkType_10b6b330_List unk_54;
};

// UnkType_10b6b330::Unk_10b6b330
bool UnkType_10b6b330::Unk_10b6b330()
{
    if ( unk_14 )
    {
        Unk_10b71ee0(unk_1c);
        unk_28.Empty();
        unk_4c = 30.0f;
        unk_54.Unk_1090d670(0);
        unk_40 = 0;
        unk_44 = 0;
        unk_48 = 0;
        unk_3c = 0;
        unk_15 = false;
        unk_52 = false;
        unk_51 = false;
        unk_50 = false;
        unk_10 = 0;
        unk_24 = 0;
        unk_1c = 0;
        unk_18 = 0;
        unk_14 = false;
    }
    return true;
}
