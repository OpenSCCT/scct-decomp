// campaign_leaf_220480.cpp -- a member function at VA 0x10b20480: from the last element to the
// first, it calls virtual slot 2 of each object the array at 0x98 points to and deletes it through
// its virtual destructor; then it empties the array (its block is reallocated to no bytes through
// virtual slot 1 of the allocator the global at VA 0x111c88a0 points to, tagged L"FArray::INT"),
// clears the int at 0x40, calls the member at VA 0x10a0da80 and returns 1. The class, method and
// member names are invented; the offsets, addresses, string and slots are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10b20480_Item
{
public:
    virtual ~UnkType_10b20480_Item();
    virtual void Realloc();
    virtual void Free();
};

class UnkType_10b20480_Items
{
public:
    // guess: removes every element and frees the block (an inline helper; name invented)
    void Empty()
    {
        unk_04 = 0;
        unk_08 = 0;
        unk_00 = (UnkType_10b20480_Item**)GUnk_111c88a0->Realloc(unk_00, 0, L"FArray::INT");
    }

    UnkType_10b20480_Item** unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10b20480
{
public:
    void Unk_10a0da80();
    int Unk_10b20480();

private:
    unsigned char unk_00[0x40];
    int unk_40;
    unsigned char unk_44[0x98 - 0x44];
    UnkType_10b20480_Items unk_98;
};

// UnkType_10b20480::Unk_10b20480
int UnkType_10b20480::Unk_10b20480()
{
    for ( int i = unk_98.unk_04 - 1; i >= 0; i-- )
    {
        UnkType_10b20480_Item* Item = unk_98.unk_00[i];
        if ( Item )
        {
            Item->Free();
            delete Item;
        }
    }
    unk_98.Empty();
    unk_40 = 0;
    Unk_10a0da80();
    return 1;
}
