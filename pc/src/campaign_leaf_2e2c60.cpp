// campaign_leaf_2e2c60.cpp -- method at VA 0x10be2c60 of a dynamic array (data pointer, count,
// capacity) of 20-byte elements holding a dynamic array at 0x08, taking a capacity: destroys every
// element (the inner array's contents removed through the method at VA 0x10bdf500, its data freed
// through virtual slot 2 of the allocator at VA 0x111c88a0, its three words cleared), sets the
// count to 0 and the capacity to the argument, and reallocates the data to that many elements
// through virtual slot 1 of the allocator, tagged L"FArray". The class, member and method names are
// invented; the offsets and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10be2c60_08
{
public:
    ~UnkType_10be2c60_08()
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

class UnkType_10be2c60_Elem
{
public:
    int unk_00;
    int unk_04;
    UnkType_10be2c60_08 unk_08;
};

class UnkType_10be2c60
{
public:
    void Unk_10be2c60(int Capacity);

private:
    UnkType_10be2c60_Elem* unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_10be2c60::Unk_10be2c60
void UnkType_10be2c60::Unk_10be2c60(int Capacity)
{
    for ( int Index = 0; Index < unk_04; Index++ )
    {
        unk_00[Index].~UnkType_10be2c60_Elem();
    }
    unk_08 = Capacity;
    unk_04 = 0;
    unk_00 = (UnkType_10be2c60_Elem*)GUnk_111c88a0->Realloc(
        unk_00, unk_08 * sizeof(UnkType_10be2c60_Elem), L"FArray");
}
