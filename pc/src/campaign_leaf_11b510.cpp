// campaign_leaf_11b510.cpp -- one function at file offset 0x11b510, preferred VA 0x10a1b510.
// It appends a 0x18-byte entry to the array its argument refers to, growing the array through the
// allocator at VA 0x111c88a0 with the tag "FArray", and fills the entry with the pointer at VA
// 0x111f5f4c (created on first use by the functions at VA 0x1096b640 and 0x1096b6b0) and zero.
// The class, method and member names are invented; the offset and the bytes are the binary's.

#include "campaign_global_111c88a0.h"
#include "campaign_global_111f5f4c.h"

void* Unk_1096b640(const unsigned short* Package);
void Unk_1096b6b0();

inline void* GetUnk111f5f4c()
{
    if ( !GUnk_111f5f4c )
    {
        GUnk_111f5f4c = Unk_1096b640(L"Engine");
        Unk_1096b6b0();
    }
    return GUnk_111f5f4c;
}

struct UnkType_10a1b510_List
{
    void* unk_0;
    int unk_4;
    int unk_8;

    UnkType_10a1b510_List()
        : unk_0(0), unk_4(0), unk_8(0)
    {
    }
};

struct UnkType_10a1b510_Entry
{
    void* unk_0;
    int unk_4;
    int unk_8;
    UnkType_10a1b510_List unk_c;
};

struct UnkType_10a1b510_Array
{
    UnkType_10a1b510_Entry* Data;
    int ArrayNum;
    int ArrayMax;
};

inline void* operator new(unsigned int Size, UnkType_10a1b510_Array& Array)
{
    int Index = Array.ArrayNum;
    if ( ++Array.ArrayNum > Array.ArrayMax )
    {
        Array.ArrayMax = Array.ArrayNum + 3 * Array.ArrayNum / 8 + 2;
        Array.Data = (UnkType_10a1b510_Entry*)GUnk_111c88a0->Realloc(Array.Data,
            Array.ArrayMax * sizeof(UnkType_10a1b510_Entry), L"FArray");
    }
    return &Array.Data[Index];
}

class UnkType_10a1b510
{
public:
    void Unk_10a1b510(UnkType_10a1b510_Array& Array);
};

// UnkType_10a1b510::Unk_10a1b510
void UnkType_10a1b510::Unk_10a1b510(UnkType_10a1b510_Array& Array)
{
    UnkType_10a1b510_Entry* Entry = new(Array) UnkType_10a1b510_Entry;
    Entry->unk_0 = GetUnk111f5f4c();
    Entry->unk_4 = 0;
}
