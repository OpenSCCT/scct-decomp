// campaign_leaf_0bf870.cpp -- method at VA 0x109bf870 of a dynamic array of 0x28-byte records (data
// pointer at 0x00, count at 0x04, capacity at 0x08) taking a capacity: destroys every record (the
// two-word dynamic array at 0x00 of each: method at VA 0x10ccb3f0 with 0, its count and the element
// size 2, then frees its data through virtual slot 2 of the allocator global at VA 0x111c88a0),
// zeroes the count, stores the argument as the capacity and reallocates the data through virtual
// slot 1 of the same object with the tag "FArray". guess: an instance of the engine's
// TArray<T>::Empty. The class, member and method names are invented; the offsets and the addresses
// are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_109bf870_Array
{
public:
    ~UnkType_109bf870_Array()
    {
        Unk_10ccb3f0(0, unk_04, 2);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = 0;
    }

    void Unk_10ccb3f0(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
};

struct UnkType_109bf870_Record
{
    UnkType_109bf870_Array unk_00;
    int unk_08;
    int unk_0c;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1c;
    int unk_20;
    int unk_24;
};

class UnkType_109bf870
{
public:
    void Unk_109bf870(int Slack);

private:
    UnkType_109bf870_Record* unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_109bf870::Unk_109bf870
void UnkType_109bf870::Unk_109bf870(int Slack)
{
    for ( int i = 0; i < unk_04; i++ )
    {
        unk_00[i].~UnkType_109bf870_Record();
    }
    unk_04 = 0;
    unk_08 = Slack;
    unk_00 = (UnkType_109bf870_Record*)GUnk_111c88a0->Realloc(
        unk_00, Slack * sizeof(UnkType_109bf870_Record), L"FArray");
}
