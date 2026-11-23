// campaign_leaf_139920.cpp -- one function at file offset 0x139920, preferred VA 0x10a39920.
// A destructor: it installs its class's virtual tables at offsets 0, 0x28 and 0x2c, calls the
// base's method at VA 0x10cd7a30, destroys the array of 4-byte elements at offset 0x4c (its
// method at VA 0x10a0b9a0 removes every element, the allocator at VA 0x111c88a0 frees the block)
// and runs the base destructor at VA 0x10cdc460.
// The class and member names are invented; the offset and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10a39920_Base
{
public:
    virtual ~UnkType_10a39920_Base();

    void Unk_10cd7a30();

    unsigned char unk_4[0x28 - 0x4];
};

class UnkType_10a39920_First
{
public:
    virtual void Malloc();
};

class UnkType_10a39920_Second
{
public:
    virtual void Malloc();
};

class UnkType_10a39920_Array
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10a0b9a0(int Index, int Count, int ElementSize);

    ~UnkType_10a39920_Array()
    {
        Unk_10a0b9a0(0, ArrayNum, 4);
        if ( Data )
        {
            GUnk_111c88a0->Free(Data);
        }
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

class UnkType_10a39920 : public UnkType_10a39920_Base, public UnkType_10a39920_First,
    public UnkType_10a39920_Second
{
public:
    unsigned char unk_30[0x4c - 0x30];
    UnkType_10a39920_Array unk_4c;

    virtual ~UnkType_10a39920();
};

// UnkType_10a39920::~UnkType_10a39920
UnkType_10a39920::~UnkType_10a39920()
{
    Unk_10cd7a30();
}
