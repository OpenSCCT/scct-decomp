// campaign_leaf_10f830.cpp -- one function at file offset 0x10f830, preferred VA 0x10a0f830.
// A destructor of a class three levels above the object base: each level installs its virtual
// table and calls the base's method at VA 0x10cd7a30. The most derived level destroys the array
// of 4-byte elements at offset 0x8c (its method at VA 0x10991ae0 removes every element) and the
// array at offset 0x34 (its method at VA 0x1090d050), freeing each block through the allocator
// at VA 0x111c88a0; the last level runs the base destructor at VA 0x10cdc460.
// The class and member names are invented; the offset and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10a0f830_Object
{
public:
    virtual ~UnkType_10a0f830_Object();

    void Unk_10cd7a30();

    unsigned char unk_4[0x28 - 0x4];
};

class UnkType_10a0f830_Base : public UnkType_10a0f830_Object
{
public:
    virtual ~UnkType_10a0f830_Base()
    {
        Unk_10cd7a30();
    }
};

class UnkType_10a0f830_Middle : public UnkType_10a0f830_Base
{
public:
    unsigned char unk_28[0x34 - 0x28];

    virtual ~UnkType_10a0f830_Middle()
    {
        Unk_10cd7a30();
    }
};

class UnkType_10a0f830_Array
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_1090d050(int Index, int Count);

    ~UnkType_10a0f830_Array()
    {
        Unk_1090d050(0, ArrayNum);
        if ( Data )
        {
            GUnk_111c88a0->Free(Data);
        }
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

class UnkType_10a0f830_PointerArray
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10991ae0(int Index, int Count, int ElementSize);

    ~UnkType_10a0f830_PointerArray()
    {
        Unk_10991ae0(0, ArrayNum, 4);
        if ( Data )
        {
            GUnk_111c88a0->Free(Data);
        }
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

class UnkType_10a0f830 : public UnkType_10a0f830_Middle
{
public:
    UnkType_10a0f830_Array unk_34;
    unsigned char unk_40[0x8c - 0x40];
    UnkType_10a0f830_PointerArray unk_8c;

    virtual ~UnkType_10a0f830();
};

// UnkType_10a0f830::~UnkType_10a0f830
UnkType_10a0f830::~UnkType_10a0f830()
{
    Unk_10cd7a30();
}
