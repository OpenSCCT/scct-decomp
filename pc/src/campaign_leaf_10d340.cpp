// campaign_leaf_10d340.cpp -- one function at file offset 0x10d340, preferred VA 0x10a0d340.
// A destructor of a class three levels above the object base: each level installs its virtual
// table and calls the base's method at VA 0x10cd7a30. The most derived level empties and destroys
// its sixteen arrays of 2-byte elements at offsets 0x58 to 0x118 (the method at VA 0x10907710
// removes every element; the allocator at VA 0x111c88a0 reallocates and frees the blocks) and the
// string at offset 0x4c (destructor at VA 0x1090ba70); the base destructor at VA 0x10cdc460 runs
// last.
// The class and member names are invented; the offset and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10a0d340_Object
{
public:
    virtual ~UnkType_10a0d340_Object();

    void Unk_10cd7a30();

    unsigned char unk_4[0x28 - 0x4];
};

class UnkType_10a0d340_Base : public UnkType_10a0d340_Object
{
public:
    virtual ~UnkType_10a0d340_Base()
    {
        Unk_10cd7a30();
    }
};

class UnkType_10a0d340_Middle : public UnkType_10a0d340_Base
{
public:
    unsigned char unk_28[0x4c - 0x28];

    virtual ~UnkType_10a0d340_Middle()
    {
        Unk_10cd7a30();
    }
};

class UnkType_10a0d340_String
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    ~UnkType_10a0d340_String();
};

class UnkType_10a0d340_Array
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10907710(int Index, int Count, int ElementSize);

    ~UnkType_10a0d340_Array()
    {
        Unk_10907710(0, ArrayNum, 2);
        if ( Data )
        {
            GUnk_111c88a0->Free(Data);
        }
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

class UnkType_10a0d340_WordArray : public UnkType_10a0d340_Array
{
public:
    ~UnkType_10a0d340_WordArray()
    {
        Empty();
    }

    void Empty()
    {
        ArrayNum = 0;
        ArrayMax = 0;
        Data = GUnk_111c88a0->Realloc(Data, ArrayMax * 2, L"FArray::_WORD");
    }
};

class UnkType_10a0d340 : public UnkType_10a0d340_Middle
{
public:
    UnkType_10a0d340_String unk_4c;
    UnkType_10a0d340_WordArray unk_58[16];

    virtual ~UnkType_10a0d340();
};

// UnkType_10a0d340::~UnkType_10a0d340
UnkType_10a0d340::~UnkType_10a0d340()
{
    Unk_10cd7a30();
}
