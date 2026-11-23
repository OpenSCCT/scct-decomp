// campaign_leaf_0c4a00.cpp -- method at VA 0x109c4a00: when the pointer at 0x12c is set, destroys
// the dynamic array at 0x14 of that object (method at VA 0x10977960 with 0, its count and the
// element size 4, then frees its data), frees the object, both through virtual slot 2 of the
// allocator global at VA 0x111c88a0, and clears the pointer; then tail-calls the method at VA
// 0x10cd8ea0. The class, member and method names are invented; the offsets and the addresses are
// the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_109c4a00_Array
{
public:
    ~UnkType_109c4a00_Array()
    {
        Unk_10977960(0, unk_04, 4);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10977960(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109c4a00_Owned
{
public:
    void operator delete(void* Block)
    {
        GUnk_111c88a0->Free(Block);
    }

private:
    unsigned char unk_00[0x14];
    UnkType_109c4a00_Array unk_14;
};

class UnkType_109c4a00
{
public:
    void Unk_109c4a00();
    void Unk_10cd8ea0();

private:
    unsigned char unk_00[0x12c];
    UnkType_109c4a00_Owned* unk_12c;
};

// UnkType_109c4a00::Unk_109c4a00
void UnkType_109c4a00::Unk_109c4a00()
{
    if ( unk_12c )
    {
        delete unk_12c;
        unk_12c = 0;
    }
    Unk_10cd8ea0();
}
