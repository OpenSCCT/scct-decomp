// campaign_leaf_146f50.cpp -- one function at file offset 0x146f50, preferred VA 0x10a46f50.
// A destructor: it installs its class's virtual tables at offsets 0, 0x28 and 0x2c, calls the
// base's method at VA 0x10cd7a30, destroys the array of 4-byte elements at offset 0x1b0 (its
// method at VA 0x10929170 removes every element, the allocator at VA 0x111c88a0 frees the block)
// and the strings at offsets 0x168 and 0x15c (destructor at VA 0x1090ba70), and runs the base
// destructor at VA 0x10a39920.
// The class and member names are invented; the offset and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10a46f50_Object
{
public:
    virtual ~UnkType_10a46f50_Object();

    void Unk_10cd7a30();

    unsigned char unk_4[0x28 - 0x4];
};

class UnkType_10a46f50_First
{
public:
    virtual void Malloc();
};

class UnkType_10a46f50_Second
{
public:
    virtual void Malloc();
};

class UnkType_10a46f50_Base : public UnkType_10a46f50_Object, public UnkType_10a46f50_First,
    public UnkType_10a46f50_Second
{
public:
    unsigned char unk_30[0x15c - 0x30];

    virtual ~UnkType_10a46f50_Base();
};

class UnkType_10a46f50_String
{
public:
    void* unk_0;
    int unk_4;
    int unk_8;

    ~UnkType_10a46f50_String();
};

class UnkType_10a46f50_Array
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10929170(int Index, int Count, int ElementSize);

    ~UnkType_10a46f50_Array()
    {
        Unk_10929170(0, ArrayNum, 4);
        if ( Data )
        {
            GUnk_111c88a0->Free(Data);
        }
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

class UnkType_10a46f50 : public UnkType_10a46f50_Base
{
public:
    UnkType_10a46f50_String unk_15c;
    UnkType_10a46f50_String unk_168;
    unsigned char unk_174[0x1b0 - 0x174];
    UnkType_10a46f50_Array unk_1b0;

    virtual ~UnkType_10a46f50();
};

// UnkType_10a46f50::~UnkType_10a46f50
UnkType_10a46f50::~UnkType_10a46f50()
{
    Unk_10cd7a30();
}
