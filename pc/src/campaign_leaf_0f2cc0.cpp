// campaign_leaf_0f2cc0.cpp -- method at VA 0x109f2cc0 of a dynamic array of 12-byte dynamic arrays
// (data pointer at 0x00, count at 0x04, capacity at 0x08) taking a capacity: destroys every element
// (method at VA 0x109d9760 with 0, its count and the element size 0x10, then frees its data through
// virtual slot 2 of the allocator global at VA 0x111c88a0), zeroes the count, stores the argument
// as the capacity and reallocates the data through virtual slot 1 of the same object with the tag
// "FArray". guess: an instance of the engine's TArray<T>::Empty. The class, member and method names
// are invented; the offsets and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_109f2cc0_Array
{
public:
    ~UnkType_109f2cc0_Array()
    {
        Unk_109d9760(0, unk_04, 0x10);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_109d9760(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109f2cc0
{
public:
    void Unk_109f2cc0(int Slack);

private:
    UnkType_109f2cc0_Array* unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_109f2cc0::Unk_109f2cc0
void UnkType_109f2cc0::Unk_109f2cc0(int Slack)
{
    for ( int i = 0; i < unk_04; i++ )
    {
        unk_00[i].~UnkType_109f2cc0_Array();
    }
    unk_04 = 0;
    unk_08 = Slack;
    unk_00 = (UnkType_109f2cc0_Array*)GUnk_111c88a0->Realloc(
        unk_00, Slack * sizeof(UnkType_109f2cc0_Array), L"FArray");
}
