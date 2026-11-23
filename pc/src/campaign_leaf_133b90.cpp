// campaign_leaf_133b90.cpp -- one function at file offset 0x133b90, preferred VA 0x10a33b90.
// A destructor: it installs its class's virtual table, calls the base's method at VA 0x10cd7a30,
// destroys the member at offset 0x3c with the destructor at VA 0x10a064f0 and the array of 4-byte
// elements at offset 0x28 (its method at VA 0x10929a90 removes every element, the allocator at VA
// 0x111c88a0 frees the block), and runs the base destructor at VA 0x10cdc460.
// The class and member names are invented; the offset and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10a33b90_Base
{
public:
    virtual ~UnkType_10a33b90_Base();

    void Unk_10cd7a30();

    unsigned char unk_4[0x28 - 0x4];
};

class UnkType_10a33b90_Array
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10929a90(int Index, int Count, int ElementSize);

    ~UnkType_10a33b90_Array()
    {
        Unk_10929a90(0, ArrayNum, 4);
        if ( Data )
        {
            GUnk_111c88a0->Free(Data);
        }
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

class UnkType_10a33b90_Member
{
public:
    unsigned char unk_0[0xc];

    ~UnkType_10a33b90_Member();
};

class UnkType_10a33b90 : public UnkType_10a33b90_Base
{
public:
    UnkType_10a33b90_Array unk_28;
    unsigned char unk_34[0x3c - 0x34];
    UnkType_10a33b90_Member unk_3c;

    virtual ~UnkType_10a33b90();
};

// UnkType_10a33b90::~UnkType_10a33b90
UnkType_10a33b90::~UnkType_10a33b90()
{
    Unk_10cd7a30();
}
