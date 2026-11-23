// campaign_leaf_093690.cpp -- method at VA 0x10993690: releases every object in the pointer array at
// 0x170 (count at 0x174, capacity at 0x178), deleting an object through its virtual destructor
// (vtable slot 3) when the reference count at 0x28 drops to 0; empties the array (zeroes count and
// capacity and reallocates the data to nothing through virtual slot 1 of the allocator global at
// VA 0x111c88a0 with the tag "FArray"); frees and clears the pointers at 0xdc, 0x21c, 0xe0 and
// 0x218 through virtual slot 2 of the same object; then calls the method at VA 0x10992c20 and ends
// in the method at VA 0x10cd8ea0. The class, member and method names are invented; the offsets,
// the slots and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10993690_Item
{
public:
    virtual void Malloc();
    virtual void Realloc();
    virtual void Free();
    virtual ~UnkType_10993690_Item();

    unsigned char unk_04[0x28 - 0x04];
    int unk_28;
};

class UnkType_10993690
{
public:
    void Unk_10993690();
    void Unk_10992c20();
    void Unk_10cd8ea0();

private:
    unsigned char unk_00[0xdc];
    void* unk_dc;
    void* unk_e0;
    unsigned char unk_e4[0x170 - 0xe4];
    UnkType_10993690_Item** unk_170;
    int unk_174;
    int unk_178;
    unsigned char unk_17c[0x218 - 0x17c];
    void* unk_218;
    void* unk_21c;
};

// UnkType_10993690::Unk_10993690
void UnkType_10993690::Unk_10993690()
{
    for ( int i = 0; i < unk_174; i++ )
    {
        UnkType_10993690_Item* Item = unk_170[i];
        if ( --Item->unk_28 == 0 )
        {
            delete Item;
        }
    }
    unk_174 = 0;
    unk_178 = 0;
    unk_170 = (UnkType_10993690_Item**)GUnk_111c88a0->Realloc(
        unk_170, unk_178 * sizeof(UnkType_10993690_Item*), L"FArray");
    if ( unk_dc )
    {
        GUnk_111c88a0->Free(unk_dc);
        unk_dc = 0;
    }
    if ( unk_21c )
    {
        GUnk_111c88a0->Free(unk_21c);
        unk_21c = 0;
    }
    if ( unk_e0 )
    {
        GUnk_111c88a0->Free(unk_e0);
        unk_e0 = 0;
    }
    if ( unk_218 )
    {
        GUnk_111c88a0->Free(unk_218);
        unk_218 = 0;
    }
    Unk_10992c20();
    Unk_10cd8ea0();
}
