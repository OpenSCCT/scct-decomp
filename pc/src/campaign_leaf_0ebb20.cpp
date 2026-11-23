// campaign_leaf_0ebb20.cpp -- destructor at VA 0x109ebb20: destroys the dynamic array at 0x30
// (method at VA 0x109e0c70 with 0 and its count, then frees its data), the 12-byte member at 0x24
// (frees its pointer at 0x08) and the dynamic array at 0x18 like the first, all through virtual
// slot 2 of the allocator global at VA 0x111c88a0. The class, member and method names are invented;
// the offsets and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_109ebb20_List
{
public:
    ~UnkType_109ebb20_List()
    {
        Unk_109e0c70(0, unk_04);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_109e0c70(int Index, int Count);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109ebb20_Block
{
public:
    ~UnkType_109ebb20_Block()
    {
        GUnk_111c88a0->Free(unk_08);
    }

private:
    int unk_00;
    int unk_04;
    void* unk_08;
};

class UnkType_109ebb20
{
public:
    ~UnkType_109ebb20();

private:
    unsigned char unk_00[0x18];
    UnkType_109ebb20_List unk_18;
    UnkType_109ebb20_Block unk_24;
    UnkType_109ebb20_List unk_30;
};

// UnkType_109ebb20::~UnkType_109ebb20
UnkType_109ebb20::~UnkType_109ebb20()
{
}
