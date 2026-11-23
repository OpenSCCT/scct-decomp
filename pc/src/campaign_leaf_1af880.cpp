// campaign_leaf_1af880.cpp -- destructor at VA 0x10aaf880 of a class whose only member is an array
// of object pointers at 0x00. The body deletes every object through its virtual destructor; the
// array is then destroyed: its method at VA 0x10aadf30 removes all its 4-byte elements, its data is
// freed through slot 2 of the allocator at VA 0x111c88a0, and its three words are cleared. The
// class, method and member names are invented.

#include "campaign_global_111c88a0.h"

class UnkType_10aaf880_Item
{
public:
    virtual ~UnkType_10aaf880_Item();
};

class UnkType_10aadf30
{
public:
    // UnkType_10aadf30::~UnkType_10aadf30
    ~UnkType_10aadf30()
    {
        Unk_10aadf30(0, unk_4, 4);
        if ( unk_0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_4 = unk_8 = 0;
    }

    void Unk_10aadf30(int Index, int Count, int ElementSize);

    UnkType_10aaf880_Item** unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10aaf880
{
public:
    ~UnkType_10aaf880();

private:
    UnkType_10aadf30 unk_0;
};

// UnkType_10aaf880::~UnkType_10aaf880
UnkType_10aaf880::~UnkType_10aaf880()
{
    for ( int i = 0; i < unk_0.unk_4; i++ )
    {
        delete unk_0.unk_0[i];
    }
}
