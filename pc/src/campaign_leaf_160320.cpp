// campaign_leaf_160320.cpp -- one function at file offset 0x160320, preferred VA 0x10a60320.
// It empties an array of 0x1c-byte elements: it destroys every element with the destructor at
// VA 0x109c6a20, sets the count to 0 and the capacity to its argument, and reallocates the block
// through the allocator at VA 0x111c88a0 (tag "FArray").
// The class, method and member names are invented; the offset and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10a60320_Element
{
public:
    unsigned char unk_0[0x1c];

    ~UnkType_10a60320_Element();
};

class UnkType_10a60320
{
public:
    UnkType_10a60320_Element* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10a60320(int Slack);
};

// UnkType_10a60320::Unk_10a60320
void UnkType_10a60320::Unk_10a60320(int Slack)
{
    for ( int i = 0; i < ArrayNum; i++ )
    {
        Data[i].~UnkType_10a60320_Element();
    }
    ArrayNum = 0;
    ArrayMax = Slack;
    Data = (UnkType_10a60320_Element*)GUnk_111c88a0->Realloc(Data,
        ArrayMax * sizeof(UnkType_10a60320_Element), L"FArray");
}
