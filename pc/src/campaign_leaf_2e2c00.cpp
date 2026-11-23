// campaign_leaf_2e2c00.cpp -- method at VA 0x10be2c00 of a dynamic array (data pointer, count) of
// 20-byte elements holding a dynamic array at 0x08: destroys every element (removing the inner
// array's contents through the method at VA 0x10bdf500, freeing its data through virtual slot 2 of
// the allocator at VA 0x111c88a0 and clearing its three words), then sets the count to 0. The
// class, member and method names are invented; the offsets and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10be2c00_08
{
public:
    ~UnkType_10be2c00_08()
    {
        Unk_10bdf500(0, unk_04);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10bdf500(int Index, int Count);

    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10be2c00_Elem
{
public:
    int unk_00;
    int unk_04;
    UnkType_10be2c00_08 unk_08;
};

class UnkType_10be2c00
{
public:
    void Unk_10be2c00();

private:
    UnkType_10be2c00_Elem* unk_00;
    int unk_04;
};

// UnkType_10be2c00::Unk_10be2c00
void UnkType_10be2c00::Unk_10be2c00()
{
    for ( int Index = 0; Index < unk_04; Index++ )
    {
        unk_00[Index].~UnkType_10be2c00_Elem();
    }
    unk_04 = 0;
}
