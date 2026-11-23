// campaign_leaf_133e90.cpp -- one function at file offset 0x133e90, preferred VA 0x10a33e90.
// A destructor: it installs its class's virtual table, calls the base's method at VA 0x10cd7a30,
// destroys the seven arrays at offsets 0x3a04 down to 0x399c (each removes every element through
// its own method, then frees its block through the allocator at VA 0x111c88a0), the entry at
// offset 0x3950 (an array at 0x40 and a base whose destructor is at VA 0x10ae10c0), the member at
// offset 0x3910 (destructor at VA 0x10ae10c0) and the string at offset 0xcc (destructor at
// VA 0x1090ba70), and runs the base destructor at VA 0x10a33b90.
// The class and member names are invented; the offset and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10a33e90_Base
{
public:
    virtual ~UnkType_10a33e90_Base();

    void Unk_10cd7a30();

    unsigned char unk_4[0xcc - 0x4];
};

class UnkType_10a33e90_ArrayA
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10929a90(int Index, int Count, int ElementSize);

    ~UnkType_10a33e90_ArrayA()
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

class UnkType_10a33e90_ArrayB
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10a31970(int Index, int Count, int ElementSize);

    ~UnkType_10a33e90_ArrayB()
    {
        Unk_10a31970(0, ArrayNum, 4);
        if ( Data )
        {
            GUnk_111c88a0->Free(Data);
        }
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

class UnkType_10a33e90_ArrayC
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10a31a00(int Index, int Count, int ElementSize);

    ~UnkType_10a33e90_ArrayC()
    {
        Unk_10a31a00(0, ArrayNum, 4);
        if ( Data )
        {
            GUnk_111c88a0->Free(Data);
        }
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

class UnkType_10a33e90_ArrayD
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10a31a90(int Index, int Count, int ElementSize);

    ~UnkType_10a33e90_ArrayD()
    {
        Unk_10a31a90(0, ArrayNum, 4);
        if ( Data )
        {
            GUnk_111c88a0->Free(Data);
        }
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

class UnkType_10a33e90_ArrayE
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    void Unk_10a31b20(int Index, int Count, int ElementSize);

    ~UnkType_10a33e90_ArrayE()
    {
        Unk_10a31b20(0, ArrayNum, 4);
        if ( Data )
        {
            GUnk_111c88a0->Free(Data);
        }
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
};

class UnkType_10a33e90_String
{
public:
    void* Data;
    int ArrayNum;
    int ArrayMax;

    ~UnkType_10a33e90_String();
};

class UnkType_10a33e90_Member
{
public:
    int unk_0;

    ~UnkType_10a33e90_Member();
};

class UnkType_10a33e90_Entry : public UnkType_10a33e90_Member
{
public:
    unsigned char unk_4[0x40 - 0x4];
    UnkType_10a33e90_ArrayA unk_40;
};

class UnkType_10a33e90 : public UnkType_10a33e90_Base
{
public:
    UnkType_10a33e90_String unk_cc;
    unsigned char unk_d8[0x3910 - 0xd8];
    UnkType_10a33e90_Member unk_3910;
    unsigned char unk_3914[0x3950 - 0x3914];
    UnkType_10a33e90_Entry unk_3950;
    UnkType_10a33e90_ArrayB unk_399c;
    unsigned char unk_39a8[0x39c0 - 0x39a8];
    UnkType_10a33e90_ArrayA unk_39c0;
    UnkType_10a33e90_ArrayA unk_39cc;
    UnkType_10a33e90_ArrayA unk_39d8;
    UnkType_10a33e90_ArrayC unk_39e4;
    UnkType_10a33e90_ArrayD unk_39f0;
    unsigned char unk_39fc[0x3a04 - 0x39fc];
    UnkType_10a33e90_ArrayE unk_3a04;

    virtual ~UnkType_10a33e90();
};

// UnkType_10a33e90::~UnkType_10a33e90
UnkType_10a33e90::~UnkType_10a33e90()
{
    Unk_10cd7a30();
}
