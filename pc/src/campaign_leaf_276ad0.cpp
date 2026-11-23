// campaign_leaf_276ad0.cpp -- method at VA 0x10b76ad0: when the object at 0x30 is set, copies that
// object's short at 0xa8 to the word at 0x24 when its vector of 60-byte entries at 0x68 holds any,
// frees the pointer at 0x1c of every entry through slot 2 of the allocator at VA 0x111c88a0 (with
// the count and the index taken as shorts), then calls the object's method at VA 0x10d2f530. The
// vector never allocates here, so the default allocator stands in. The class, member and method
// names are invented; the offsets and the addresses are the binary's.

#include <vector>

#include "campaign_global_111c88a0.h"

class UnkType_10b76ad0_Entry
{
public:
    unsigned char unk_00[0x1c];
    void* unk_1c;
    unsigned char unk_20[0x3c - 0x20];
};

class UnkType_10b76ad0_30
{
public:
    void Unk_10d2f530();

    unsigned char unk_00[0x68];
    std::vector<UnkType_10b76ad0_Entry> unk_68;
    unsigned char unk_78[0xa8 - 0x78];
    short unk_a8;
};

class UnkType_10b76ad0
{
public:
    void Unk_10b76ad0();

private:
    unsigned char unk_00[0x24];
    int unk_24;
    unsigned char unk_28[0x30 - 0x28];
    UnkType_10b76ad0_30* unk_30;
};

// UnkType_10b76ad0::Unk_10b76ad0
void UnkType_10b76ad0::Unk_10b76ad0()
{
    if ( unk_30 )
    {
        if ( (short)unk_30->unk_68.size() > 0 )
        {
            unk_24 = unk_30->unk_a8;
        }
        for ( int Index = 0; Index < (short)unk_30->unk_68.size(); Index++ )
        {
            GUnk_111c88a0->Free(unk_30->unk_68[(short)Index].unk_1c);
        }
        unk_30->Unk_10d2f530();
    }
}
