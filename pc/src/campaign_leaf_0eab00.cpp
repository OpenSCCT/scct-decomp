// campaign_leaf_0eab00.cpp -- method at VA 0x109eab00 of a dynamic array of 16-byte records (data
// pointer at 0x00, count at 0x04, capacity at 0x08) taking a capacity: destroys every record (the
// dynamic array at 0x00 of each: method at VA 0x10907710 with 0, its count and the element size 2,
// then frees its data through virtual slot 2 of the allocator global at VA 0x111c88a0), zeroes the
// count, stores the argument as the capacity and reallocates the data through virtual slot 1 of
// the same object with the tag "FArray". guess: an instance of the engine's TArray<T>::Empty. The
// class, member and method names are invented; the offsets and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_109eab00_Array
{
public:
    ~UnkType_109eab00_Array()
    {
        Unk_10907710(0, unk_04, 2);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10907710(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

struct UnkType_109eab00_Record
{
    UnkType_109eab00_Array unk_00;
    int unk_0c;
};

class UnkType_109eab00
{
public:
    void Unk_109eab00(int Slack);

private:
    UnkType_109eab00_Record* unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_109eab00::Unk_109eab00
void UnkType_109eab00::Unk_109eab00(int Slack)
{
    for ( int i = 0; i < unk_04; i++ )
    {
        unk_00[i].~UnkType_109eab00_Record();
    }
    unk_04 = 0;
    unk_08 = Slack;
    unk_00 = (UnkType_109eab00_Record*)GUnk_111c88a0->Realloc(
        unk_00, Slack * sizeof(UnkType_109eab00_Record), L"FArray");
}
