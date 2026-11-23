// campaign_leaf_1ae950.cpp -- thiscall method at VA 0x10aae950 of an array of pointers: unless the
// other array is this one, it appends each of the other array's elements, growing the data through
// slot 1 of the allocator at VA 0x111c88a0 (tag L"FArray") when the count passes the capacity. It
// returns this array. The class, method and member names are invented.

#include "campaign_global_111c88a0.h"

class UnkType_10aae950_Item;

class UnkType_10aae950;

void* operator new(unsigned int Size, UnkType_10aae950& Array);

class UnkType_10aae950
{
public:
    UnkType_10aae950& Unk_10aae950(const UnkType_10aae950& Other);

    // UnkType_10aae950::Add
    int Add(int Count, int ElementSize)
    {
        int Index = unk_4;
        if ( (unk_4 += Count) > unk_8 )
        {
            unk_8 = unk_4 + 3 * unk_4 / 8 + 2;
            unk_0 = (UnkType_10aae950_Item**)GUnk_111c88a0->Realloc(unk_0, unk_8 * ElementSize,
                                                                   L"FArray");
        }
        return Index;
    }

    UnkType_10aae950_Item** unk_0;
    int unk_4;
    int unk_8;
};

// operator new
inline void* operator new(unsigned int Size, UnkType_10aae950& Array)
{
    int Index = Array.Add(1, sizeof(UnkType_10aae950_Item*));
    return &Array.unk_0[Index];
}

// UnkType_10aae950::Unk_10aae950
UnkType_10aae950& UnkType_10aae950::Unk_10aae950(const UnkType_10aae950& Other)
{
    if ( this != &Other )
    {
        for ( int i = 0; i < Other.unk_4; i++ )
        {
            new(*this) UnkType_10aae950_Item*(Other.unk_0[i]);
        }
    }
    return *this;
}
