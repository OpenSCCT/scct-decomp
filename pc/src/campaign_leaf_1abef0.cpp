// campaign_leaf_1abef0.cpp -- thiscall method at VA 0x10aabef0. By the format word at 0x0c (3, 7
// or 8) it writes "Decompressing image format:  DXT1", "DXT3" or "DXT5" through the variadic method
// at VA 0x10cce100 of the object the global at VA 0x11230558 points to, then calls the matching
// method at VA 0x10aabb70, 0x10aabc50 or 0x10aabd80. The class, method and member names are
// invented; the strings are the binary's.

#include "campaign_global_11230558.h"

class UnkType_10aabef0
{
public:
    void Unk_10aabef0();
    void Unk_10aabb70();
    void Unk_10aabc50();
    void Unk_10aabd80();

private:
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
};

// UnkType_10aabef0::Unk_10aabef0
void UnkType_10aabef0::Unk_10aabef0()
{
    switch ( unk_0c )
    {
    case 3:
        GUnk_11230558->Unk_10cce100(L"Decompressing image format:  DXT1\n");
        Unk_10aabb70();
        break;
    case 7:
        GUnk_11230558->Unk_10cce100(L"Decompressing image format:  DXT3\n");
        Unk_10aabc50();
        break;
    case 8:
        GUnk_11230558->Unk_10cce100(L"Decompressing image format:  DXT5\n");
        Unk_10aabd80();
        break;
    }
}
