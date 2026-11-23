// campaign_leaf_1f8990.cpp -- thiscall method at VA 0x10af8990 of an array of 0x14-byte elements,
// taking a slack count. It destroys every element (each holds an array at 0x08 whose method at VA
// 0x10929170 removes all its 4-byte elements, after which its data is freed through slot 2 of the
// allocator at VA 0x111c88a0 and its three words are cleared), then empties the array, reallocating
// its data for the slack through slot 1 (tag L"FArray"). The class, method and member names are
// invented.

#include "campaign_global_111c88a0.h"

class UnkType_10af8990_Array
{
public:
    // UnkType_10af8990_Array::~UnkType_10af8990_Array
    ~UnkType_10af8990_Array()
    {
        Unk_10929170(0, unk_4, 4);
        if ( unk_0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_4 = unk_8 = 0;
    }

    void Unk_10929170(int Index, int Count, int ElementSize);

private:
    void* unk_0;
    int unk_4;
    int unk_8;
};

struct UnkType_10af8990_Element
{
    int unk_00;
    int unk_04;
    UnkType_10af8990_Array unk_08;
};

class UnkType_10af8990
{
public:
    void Unk_10af8990(int Slack);

private:
    UnkType_10af8990_Element* unk_0;
    int unk_4;
    int unk_8;
};

// UnkType_10af8990::Unk_10af8990
void UnkType_10af8990::Unk_10af8990(int Slack)
{
    for ( int i = 0; i < unk_4; i++ )
    {
        (&unk_0[i])->~UnkType_10af8990_Element();
    }
    unk_4 = 0;
    unk_8 = Slack;
    unk_0 = (UnkType_10af8990_Element*)GUnk_111c88a0->Realloc(
        unk_0, unk_8 * sizeof(UnkType_10af8990_Element), L"FArray");
}
