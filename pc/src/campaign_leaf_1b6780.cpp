// campaign_leaf_1b6780.cpp -- thiscall method at VA 0x10ab6780 taking an object and an unused word.
// It empties the array at 0xa8 (data reallocated to nothing through slot 1 of the allocator at VA
// 0x111c88a0, tag L"FArray") and calls the method at VA 0x10982140 of the member at 0xb4 with 0.
// When the word at 0x5c is set it builds a temporary from the object's word at 0x7c and this object
// (constructor at VA 0x10ab6410) and destroys it again: the method at VA 0x10ab6350 of its array at
// 0x08 removes all the array's elements and the array's data is freed through slot 2. The class,
// method and member names are invented.

#include "campaign_global_111c88a0.h"

class UnkType_10ab6780;

class UnkType_10ab6780_List
{
public:
    // UnkType_10ab6780_List::~UnkType_10ab6780_List
    ~UnkType_10ab6780_List()
    {
        Unk_10ab6350(0, unk_4);
        if ( unk_0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_4 = unk_8 = 0;
    }

    void Unk_10ab6350(int Index, int Count);

private:
    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10ab6780_Query
{
public:
    UnkType_10ab6780_Query(int Value, UnkType_10ab6780* Owner);

private:
    int unk_0;
    int unk_4;
    UnkType_10ab6780_List unk_8;
    int unk_14;
};

class UnkType_10ab6780_Array
{
public:
    // UnkType_10ab6780_Array::Empty
    void Empty(int Slack = 0)
    {
        unk_4 = 0;
        unk_8 = Slack;
        unk_0 = GUnk_111c88a0->Realloc(unk_0, unk_8 * 4, L"FArray");
    }

private:
    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10ab6780_Member
{
public:
    void Unk_10982140(int Value);
};

struct UnkType_10ab6780_Source
{
    char unk_00[0x7c];
    int unk_7c;
};

class UnkType_10ab6780
{
public:
    void Unk_10ab6780(UnkType_10ab6780_Source* Source, int Unused);

private:
    char unk_00[0x5c];
    int unk_5c;
    char unk_60[0xa8 - 0x60];
    UnkType_10ab6780_Array unk_a8;
    UnkType_10ab6780_Member unk_b4;
};

// UnkType_10ab6780::Unk_10ab6780
void UnkType_10ab6780::Unk_10ab6780(UnkType_10ab6780_Source* Source, int Unused)
{
    unk_a8.Empty();
    unk_b4.Unk_10982140(0);
    if ( unk_5c )
    {
        UnkType_10ab6780_Query Query(Source->unk_7c, this);
    }
}
