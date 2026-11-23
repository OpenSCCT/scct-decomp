// campaign_leaf_373920.cpp -- one function at file offset 0x373920, preferred VA 0x10c73920. It
// empties the array at 0x0 of 12-byte elements, each itself an array whose 4-byte elements the
// method at 0x10929170 removes before its data is freed through the allocator at 0x111c88a0;
// then it sets the capacity at 0x8 to Slack, the count at 0x4 to 0, and reallocates the data
// for Slack elements with the retail tag "FArray". The class, method, local and parameter names
// are invented; the offsets, the string and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10929170
{
public:
    ~UnkType_10929170()
    {
        Unk_10929170(0, unk_4, 4);
        if ( unk_0 != 0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_8 = 0;
        unk_4 = 0;
    }

    void Unk_10929170(int Index, int Count, int Size);

    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10c73920
{
public:
    void Unk_10c73920(int Slack);

    UnkType_10929170* unk_0;
    int unk_4;
    int unk_8;
};

// UnkType_10c73920::Unk_10c73920
void UnkType_10c73920::Unk_10c73920(int Slack)
{
    int Index;

    for ( Index = 0; Index < unk_4; Index++ )
    {
        unk_0[Index].~UnkType_10929170();
    }
    unk_8 = Slack;
    unk_4 = 0;
    unk_0 = (UnkType_10929170*)GUnk_111c88a0->Realloc(unk_0, Slack * sizeof(UnkType_10929170),
        L"FArray");
}
