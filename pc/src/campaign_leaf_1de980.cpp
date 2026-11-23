// campaign_leaf_1de980.cpp -- destructor at VA 0x10ade980. When the block at 0x5c is set it calls
// the class's method at VA 0x10ade5b0 with 0; then the map at 0x8c is destroyed (its hash freed
// through slot 2 of the allocator at VA 0x111c88a0 and cleared, its pair array of 0x0c-byte
// elements emptied through VA 0x10aade50, freed and cleared), and the base destructor at VA
// 0x10b0d8a0 runs. The class, method and member names are invented.

#include "campaign_global_111c88a0.h"

class UnkType_10aade50
{
public:
    // UnkType_10aade50::~UnkType_10aade50
    ~UnkType_10aade50()
    {
        Unk_10aade50(0, unk_4, 0xc);
        if ( unk_0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_4 = unk_8 = 0;
    }

    void Unk_10aade50(int Index, int Count, int ElementSize);

private:
    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10ade980_Map
{
public:
    // UnkType_10ade980_Map::~UnkType_10ade980_Map
    ~UnkType_10ade980_Map()
    {
        if ( unk_0c )
        {
            GUnk_111c88a0->Free(unk_0c);
        }
        unk_0c = 0;
        unk_10 = 0;
    }

private:
    UnkType_10aade50 unk_00;
    int* unk_0c;
    int unk_10;
};

class UnkType_10ade980_Base
{
public:
    ~UnkType_10ade980_Base();

private:
    char unk_00[0x5c];
};

class UnkType_10ade980 : public UnkType_10ade980_Base
{
public:
    ~UnkType_10ade980();

    void Unk_10ade5b0(int Value);

private:
    void* unk_5c;
    char unk_60[0x8c - 0x60];
    UnkType_10ade980_Map unk_8c;
};

// UnkType_10ade980::~UnkType_10ade980
UnkType_10ade980::~UnkType_10ade980()
{
    if ( unk_5c )
    {
        Unk_10ade5b0(0);
    }
}
