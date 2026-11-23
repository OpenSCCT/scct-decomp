// campaign_leaf_20ea40.cpp -- thiscall method at VA 0x10b0ea40 of an array of 0x64-byte elements
// (data, count, capacity) whose element class has a virtual destructor. Given a new capacity, it
// destroys every element in place, sets the capacity, clears the count and reallocates the data
// through slot 1 of the allocator at VA 0x111c88a0 with the tag "FArray". The class, method and
// member names are invented; the tag is the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10b0ea40_Element
{
public:
    virtual ~UnkType_10b0ea40_Element();

private:
    char unk_04[0x64 - 0x04];
};

class UnkType_10b0ea40
{
public:
    void Unk_10b0ea40(int Slack);

private:
    UnkType_10b0ea40_Element* unk_0;
    int unk_4;
    int unk_8;
};

// UnkType_10b0ea40::Unk_10b0ea40
void UnkType_10b0ea40::Unk_10b0ea40(int Slack)
{
    for ( int i = 0; i < unk_4; i++ )
    {
        unk_0[i].~UnkType_10b0ea40_Element();
    }
    unk_8 = Slack;
    unk_4 = 0;
    unk_0 = (UnkType_10b0ea40_Element*)GUnk_111c88a0->Realloc(
        unk_0, Slack * sizeof(UnkType_10b0ea40_Element), L"FArray");
}
