// campaign_leaf_210990.cpp -- a member function at VA 0x10b10990 of an array of 0x20-byte elements
// taking a slack count: it destroys the string at the start of each element (it is emptied, its
// block reallocated to no bytes through virtual slot 1 of the allocator the global at VA
// 0x111c88a0 points to, tagged L"FArray::_WORD"; then the member at VA 0x10907710 removes all its
// 2-byte characters, its block is freed through virtual slot 2 of that allocator and it is
// cleared), then sets the capacity to the slack count and the count to 0 and reallocates the block
// to that capacity through virtual slot 1, tagged L"FArray". guess: empties the array. The class,
// method and member names are invented; the offsets, sizes, addresses, strings and slots are the
// binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10b10990_Array
{
public:
    void Unk_10907710(int Index, int Count, int Size);

    // guess: removes the characters and frees the block (an inline destructor)
    ~UnkType_10b10990_Array()
    {
        Unk_10907710(0, unk_04, 2);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_08 = 0;
        unk_04 = 0;
    }

protected:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10b10990_String : public UnkType_10b10990_Array
{
public:
    // guess: empties the string first (an inline destructor)
    ~UnkType_10b10990_String()
    {
        unk_04 = 0;
        unk_08 = 0;
        unk_00 = GUnk_111c88a0->Realloc(unk_00, 0, L"FArray::_WORD");
    }
};

class UnkType_10b10990_Element
{
private:
    UnkType_10b10990_String unk_00;
    int unk_0c;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1c;
};

class UnkType_10b10990
{
public:
    void Unk_10b10990(int Slack);

private:
    UnkType_10b10990_Element* unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_10b10990::Unk_10b10990
void UnkType_10b10990::Unk_10b10990(int Slack)
{
    for ( int i = 0; i < unk_04; i++ )
    {
        ( &unk_00[i] )->~UnkType_10b10990_Element();
    }
    unk_08 = Slack;
    unk_04 = 0;
    unk_00 = (UnkType_10b10990_Element*)GUnk_111c88a0->Realloc(
        unk_00, unk_08 * sizeof(UnkType_10b10990_Element), L"FArray");
}
