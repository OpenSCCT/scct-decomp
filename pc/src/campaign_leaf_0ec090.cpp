// campaign_leaf_0ec090.cpp -- method at VA 0x109ec090: empties the dynamic array at 0x78 (zeroes
// its count, frees its data through virtual slot 2 of the allocator global at VA 0x111c88a0 and
// clears the pointer), then calls the method at VA 0x109e9330 of the dynamic array at 0x80 with 0.
// The class, member and method names are invented; the offsets and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_109ec090_List
{
public:
    void Empty()
    {
        unk_04 = 0;
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
    }

private:
    void* unk_00;
    int unk_04;
};

class UnkType_109ec090_Records
{
public:
    void Unk_109e9330(int Slack);
};

class UnkType_109ec090
{
public:
    void Unk_109ec090();

private:
    unsigned char unk_00[0x78];
    UnkType_109ec090_List unk_78;
    UnkType_109ec090_Records unk_80;
};

// UnkType_109ec090::Unk_109ec090
void UnkType_109ec090::Unk_109ec090()
{
    unk_78.Empty();
    unk_80.Unk_109e9330(0);
}
