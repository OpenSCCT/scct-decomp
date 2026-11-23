// campaign_leaf_10b090.cpp -- one function at file offset 0x10b090, preferred VA 0x10a0b090.
// A destructor: it installs its class's virtual table, calls the base's method at VA 0x10cd7a30,
// destroys its three entries at offset 0x80, each holding two arrays of 12-byte elements (the
// method at VA 0x10929260 removes every element, the allocator at VA 0x111c88a0 frees the block),
// and runs the base destructor at VA 0x10cdc460.
// The class and member names are invented; the offset and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10a0b090_Object
{
public:
    virtual ~UnkType_10a0b090_Object();

    void Unk_10cd7a30();

    unsigned char unk_4[0x28 - 0x4];
};

class UnkType_10a0b090_Array
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10929260(int Index, int Count, int ElementSize);

    ~UnkType_10a0b090_Array()
    {
        Unk_10929260(0, ArrayNum, 12);
        if ( Data )
        {
            GUnk_111c88a0->Free(Data);
        }
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

class UnkType_10a0b090_Entry
{
public:
    unsigned char unk_0[0x10];
    UnkType_10a0b090_Array unk_10;
    UnkType_10a0b090_Array unk_1c;
};

class UnkType_10a0b090 : public UnkType_10a0b090_Object
{
public:
    unsigned char unk_28[0x80 - 0x28];
    UnkType_10a0b090_Entry unk_80[3];

    virtual ~UnkType_10a0b090();
};

// UnkType_10a0b090::~UnkType_10a0b090
UnkType_10a0b090::~UnkType_10a0b090()
{
    Unk_10cd7a30();
}
