// campaign_leaf_1abb00.cpp -- thiscall method at VA 0x10aabb00. It frees the buffer at 0x08 through
// slot 2 of the allocator at VA 0x111c88a0 when set, allocates a new one of (0x10 times 0x14) words
// through slot 0 (tag "DXT"), writes "Error allocating decompressed byte storage" through the
// variadic method at VA 0x10cce100 of the object the global at VA 0x11230558 points to when that
// fails, and fills the buffer with zeros through the function at VA 0x10ccad40. The class, method
// and member names are invented; the strings are the binary's.

#include "campaign_global_111c88a0.h"
#include "campaign_global_11230558.h"

void Unk_10ccad40(void* Dest, int Value, int Count);

class UnkType_10aabb00
{
public:
    void Unk_10aabb00();

private:
    int unk_00;
    int unk_04;
    void* unk_08;
    int unk_0c;
    int unk_10;
    int unk_14;
};

// UnkType_10aabb00::Unk_10aabb00
void UnkType_10aabb00::Unk_10aabb00()
{
    if ( unk_08 )
    {
        GUnk_111c88a0->Free(unk_08);
        unk_08 = 0;
    }
    unk_08 = GUnk_111c88a0->Malloc(unk_10 * unk_14 * 4, L"DXT");
    if ( !unk_08 )
    {
        GUnk_11230558->Unk_10cce100(L"Error allocating decompressed byte storage\n");
    }
    Unk_10ccad40(unk_08, 0, unk_10 * unk_14 * 4);
}
