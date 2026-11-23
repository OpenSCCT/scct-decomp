// campaign_leaf_1acaa0.cpp -- thiscall method at VA 0x10aacaa0. It allocates the one-byte block
// the global at VA 0x111fa7ec points to if there is none yet (slot 0 of the allocator at VA
// 0x111c88a0, tag "UTextureStreamer"), then sets the words at 0x68, 0x74, 0x78 and 0xc4 to 1, 0x6c,
// 0x70, 0x170 and 0x174 to 0, 0xc0 to 4 and 0xc8 to 3, and stores its argument at 0xb8. The class,
// method and member names are invented; the tag is the binary's.

#include "campaign_global_111c88a0.h"
#include "campaign_global_111fa7ec.h"

class UnkType_10aacaa0
{
public:
    void Unk_10aacaa0(int Value);

private:
    char unk_000[0x68];
    int unk_068;
    int unk_06c;
    int unk_070;
    int unk_074;
    int unk_078;
    char unk_07c[0xb8 - 0x7c];
    int unk_0b8;
    int unk_0bc;
    int unk_0c0;
    int unk_0c4;
    int unk_0c8;
    char unk_0cc[0x170 - 0xcc];
    int unk_170;
    int unk_174;
};

// UnkType_10aacaa0::Unk_10aacaa0
void UnkType_10aacaa0::Unk_10aacaa0(int Value)
{
    if ( GUnk_111fa7ec == 0 )
    {
        GUnk_111fa7ec = GUnk_111c88a0->Malloc(1, L"UTextureStreamer");
    }
    unk_074 = 1;
    unk_078 = 1;
    unk_068 = 1;
    unk_0c4 = 1;
    unk_06c = 0;
    unk_070 = 0;
    unk_170 = 0;
    unk_174 = 0;
    unk_0b8 = Value;
    unk_0c0 = 4;
    unk_0c8 = 3;
}
