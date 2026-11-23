// campaign_leaf_2108f0.cpp -- a member function at VA 0x10b108f0 of an array of 0x20-byte elements
// taking an index and a count: it destroys the string at the start of each element in that range
// (it is emptied, its block reallocated to no bytes through virtual slot 1 of the allocator the
// global at VA 0x111c88a0 points to, tagged L"FArray::_WORD"; then the member at VA 0x10907710
// removes all its 2-byte characters, its block is freed through virtual slot 2 of that allocator
// and it is cleared), then passes the index, the count and the element size to the member at VA
// 0x10b103b0. guess: removes elements from the array. The class, method and member names are
// invented; the offsets, sizes, addresses, string and slots are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10b108f0_Array
{
public:
    void Unk_10907710(int Index, int Count, int Size);

    // guess: removes the characters and frees the block (an inline destructor)
    ~UnkType_10b108f0_Array()
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

class UnkType_10b108f0_String : public UnkType_10b108f0_Array
{
public:
    // guess: empties the string first (an inline destructor)
    ~UnkType_10b108f0_String()
    {
        unk_04 = 0;
        unk_08 = 0;
        unk_00 = GUnk_111c88a0->Realloc(unk_00, 0, L"FArray::_WORD");
    }
};

class UnkType_10b108f0_Element
{
private:
    UnkType_10b108f0_String unk_00;
    int unk_0c;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1c;
};

class UnkType_10b108f0
{
public:
    void Unk_10b103b0(int Index, int Count, int Size);
    void Unk_10b108f0(int Index, int Count);

private:
    UnkType_10b108f0_Element* unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_10b108f0::Unk_10b108f0
void UnkType_10b108f0::Unk_10b108f0(int Index, int Count)
{
    for ( int i = Index; i < Index + Count; i++ )
    {
        ( &unk_00[i] )->~UnkType_10b108f0_Element();
    }
    Unk_10b103b0(Index, Count, sizeof(UnkType_10b108f0_Element));
}
