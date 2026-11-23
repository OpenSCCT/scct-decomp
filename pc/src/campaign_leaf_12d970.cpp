// campaign_leaf_12d970.cpp -- one function at file offset 0x12d970, preferred VA 0x10a2d970.
// The assignment operator of an array of 12-byte elements: unless its argument is its own object,
// it empties the array, reallocates it through the allocator at VA 0x111c88a0 (tag "FArray") to
// the argument's count and appends a copy of every element of the argument; it returns its object.
// The class, method and member names are invented; the offset and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

struct UnkType_10a2d970_Element
{
    int unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10a2d970
{
public:
    UnkType_10a2d970_Element* Data;
    int ArrayNum;
    int ArrayMax;

    UnkType_10a2d970& operator=(const UnkType_10a2d970& Other);
};

inline int AddElement(UnkType_10a2d970& Array)
{
    int Index = Array.ArrayNum;
    if ( ++Array.ArrayNum > Array.ArrayMax )
    {
        Array.ArrayMax = Array.ArrayNum + 3 * Array.ArrayNum / 8 + 2;
        Array.Data = (UnkType_10a2d970_Element*)GUnk_111c88a0->Realloc(Array.Data,
            Array.ArrayMax * sizeof(UnkType_10a2d970_Element), L"FArray");
    }
    return Index;
}

inline void* operator new(unsigned int Size, void* Pointer)
{
    return Pointer;
}

// UnkType_10a2d970::operator=
UnkType_10a2d970& UnkType_10a2d970::operator=(const UnkType_10a2d970& Other)
{
    if ( this != &Other )
    {
        ArrayMax = Other.ArrayNum;
        ArrayNum = 0;
        Data = (UnkType_10a2d970_Element*)GUnk_111c88a0->Realloc(Data,
            ArrayMax * sizeof(UnkType_10a2d970_Element), L"FArray");
        for ( int i = 0; i < Other.ArrayNum; i++ )
        {
            int Index = AddElement(*this);
            new(&Data[Index]) UnkType_10a2d970_Element(Other.Data[i]);
        }
    }
    return *this;
}
