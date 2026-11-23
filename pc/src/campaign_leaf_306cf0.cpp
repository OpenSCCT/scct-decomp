// campaign_leaf_306cf0.cpp -- one function at file offset 0x306cf0, preferred VA 0x10c06cf0. A
// destructor: it installs the vtable at 0x110f5980, calls the method at 0x10cd7a30, destroys the
// arrays at 0x384 (removing its 8-byte elements with the method at 0x10c05f00) and 0x378 (emptying
// it with the method at 0x10c06b80) and 0x34c (removing its 4-byte elements with the method at
// 0x10bdb330), freeing their data through the allocator at 0x111c88a0, and ends in the base
// destructor at 0x10c068f0. The class, method and member names are invented; the offsets and the
// bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10c06cf0_Base
{
public:
    virtual ~UnkType_10c06cf0_Base();

    unsigned char unk_4[0x348];
};

class UnkType_10bdb330
{
public:
    ~UnkType_10bdb330()
    {
        Unk_10bdb330(0, unk_4, 4);
        if ( unk_0 != 0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_8 = 0;
        unk_4 = 0;
    }

    void Unk_10bdb330(int Index, int Count, int Size);

    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10c06b80
{
public:
    ~UnkType_10c06b80()
    {
        Unk_10c06b80(0, unk_4);
        if ( unk_0 != 0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_8 = 0;
        unk_4 = 0;
    }

    void Unk_10c05e70(int Index, int Count, int Size);
    void Unk_10c06b80(int Index, int Count);

    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10c05f00
{
public:
    ~UnkType_10c05f00()
    {
        Unk_10c05f00(0, unk_4, 8);
        if ( unk_0 != 0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_8 = 0;
        unk_4 = 0;
    }

    void Unk_10c05f00(int Index, int Count, int Size);

    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10c06cf0 : public UnkType_10c06cf0_Base
{
public:
    virtual ~UnkType_10c06cf0();
    void Unk_10cd7a30();

    UnkType_10bdb330 unk_34c;
    unsigned char unk_358[0x20];
    UnkType_10c06b80 unk_378;
    UnkType_10c05f00 unk_384;
};

// UnkType_10c06cf0::~UnkType_10c06cf0
UnkType_10c06cf0::~UnkType_10c06cf0()
{
    Unk_10cd7a30();
}
