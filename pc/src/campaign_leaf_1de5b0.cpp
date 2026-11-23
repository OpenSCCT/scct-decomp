// campaign_leaf_1de5b0.cpp -- thiscall method at VA 0x10ade5b0 taking one argument it does not
// read. It frees the block at 0x5c through slot 2 of the allocator at VA 0x111c88a0 when set and
// clears it, then empties the map at 0x8c: its pair array's count and capacity are cleared and its
// data reallocated to zero bytes (tag "FArray"), its hash size is set to 8 and its method at VA
// 0x10aace40 rebuilds the hash. The class, method and member names are invented; the tag is the
// binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10ade5b0_Map
{
public:
    // UnkType_10ade5b0_Map::Empty
    void Empty()
    {
        unk_04 = 0;
        unk_08 = 0;
        unk_00 = GUnk_111c88a0->Realloc(unk_00, 0, L"FArray");
        unk_10 = 8;
        Unk_10aace40();
    }

    void Unk_10aace40();

private:
    void* unk_00;
    int unk_04;
    int unk_08;
    int* unk_0c;
    int unk_10;
};

class UnkType_10ade5b0
{
public:
    void Unk_10ade5b0(int Value);

private:
    char unk_00[0x5c];
    void* unk_5c;
    char unk_60[0x8c - 0x60];
    UnkType_10ade5b0_Map unk_8c;
};

// UnkType_10ade5b0::Unk_10ade5b0
void UnkType_10ade5b0::Unk_10ade5b0(int Value)
{
    if ( unk_5c )
    {
        GUnk_111c88a0->Free(unk_5c);
        unk_5c = 0;
    }
    unk_8c.Empty();
}
