// campaign_leaf_121c70.cpp -- one function at file offset 0x121c70, preferred VA 0x10a21c70.
// guess: resets the object: empties the array at offset 0x40c (tag "FArray") and the array of
// 12-byte vectors at 0x418 (tag "FArray::FVector") through the allocator at VA 0x111c88a0, then
// calls its method at VA 0x10a1f2c0.
// The class and member names are invented; the offset and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10a21c70_Array
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Empty()
    {
        ArrayNum = 0;
        ArrayMax = 0;
        Data = GUnk_111c88a0->Realloc(Data, ArrayMax * 4, L"FArray");
    }
};

class UnkType_10a21c70_VectorArray
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Empty()
    {
        ArrayNum = 0;
        ArrayMax = 0;
        Data = GUnk_111c88a0->Realloc(Data, ArrayMax * 12, L"FArray::FVector");
    }
};

class UnkType_10a21c70
{
public:
    unsigned char unk_0[0x40c];
    UnkType_10a21c70_Array unk_40c;
    UnkType_10a21c70_VectorArray unk_418;

    void Unk_10a21c70();
    void Unk_10a1f2c0();
};

// UnkType_10a21c70::Unk_10a21c70
void UnkType_10a21c70::Unk_10a21c70()
{
    unk_40c.Empty();
    unk_418.Empty();
    Unk_10a1f2c0();
}
