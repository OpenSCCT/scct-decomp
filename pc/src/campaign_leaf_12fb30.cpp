// campaign_leaf_12fb30.cpp -- one function at file offset 0x12fb30, preferred VA 0x10a2fb30.
// A destructor: it installs its class's virtual table, calls the base's method at VA 0x10cd7a30,
// destroys the array at offset 0x4c (its method at VA 0x1090d050 removes every element), the array
// at offset 0x34 (its method at VA 0x1090d050 removes every element), freeing each block through
// the allocator at VA 0x111c88a0, and the base destructor at VA 0x10cdc460 runs last.
// The class and member names are invented; the offset and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10a2fb30_Object
{
public:
    virtual ~UnkType_10a2fb30_Object();

    void Unk_10cd7a30();

    unsigned char unk_4[0x28 - 0x4];
};

class UnkType_10a2fb30_Array
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_1090d050(int Index, int Count);

    ~UnkType_10a2fb30_Array()
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

class UnkType_10a2fb30 : public UnkType_10a2fb30_Object
{
public:
    unsigned char unk_28[0x34 - 0x28];
    UnkType_10a2fb30_Array unk_34;
    unsigned char unk_40[0x4c - 0x40];
    UnkType_10a2fb30_Array unk_4c;

    virtual ~UnkType_10a2fb30();
};

// UnkType_10a2fb30::~UnkType_10a2fb30
UnkType_10a2fb30::~UnkType_10a2fb30()
{
    Unk_10cd7a30();
}
