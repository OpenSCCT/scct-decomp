// campaign_leaf_20d8a0.cpp -- destructor at VA 0x10b0d8a0. It frees every non-null pointer held in
// the array at 0x04 through slot 2 of the allocator at VA 0x111c88a0, empties the array (its data
// reallocated to nothing through slot 1), and the array is then destroyed: its method at VA
// 0x10addf70 removes all its 4-byte elements, its data is freed and its three words are cleared.
// The class, method and member names are invented.

#include "campaign_global_111c88a0.h"

class UnkType_10addf70
{
public:
    // UnkType_10addf70::~UnkType_10addf70
    ~UnkType_10addf70()
    {
        Unk_10addf70(0, unk_4, 4);
        if ( unk_0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_4 = unk_8 = 0;
    }

    // UnkType_10addf70::Empty
    void Empty(int Slack = 0)
    {
        unk_4 = 0;
        unk_8 = Slack;
        unk_0 = (void**)GUnk_111c88a0->Realloc(unk_0, unk_8 * 4, L"FArray");
    }

    void Unk_10addf70(int Index, int Count, int ElementSize);

    void** unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10b0d8a0
{
public:
    ~UnkType_10b0d8a0();

private:
    int unk_00;
    UnkType_10addf70 unk_04;
};

// UnkType_10b0d8a0::~UnkType_10b0d8a0
UnkType_10b0d8a0::~UnkType_10b0d8a0()
{
    for ( int i = 0; i < unk_04.unk_4; i++ )
    {
        if ( unk_04.unk_0[i] )
        {
            GUnk_111c88a0->Free(unk_04.unk_0[i]);
        }
    }
    unk_04.Empty();
}
