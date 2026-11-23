// campaign_leaf_358410.cpp -- one function at file offset 0x358410, preferred VA 0x10c58410. A
// destructor: it installs the vtable at 0x111069b0, calls the method at 0x10cd7a30, destroys the
// arrays at 0x4bc (removing its 8-byte elements with the method at 0x10c57610) and 0x48c (removing
// its 4-byte elements with the method at 0x10929a90), freeing their data through the allocator at
// 0x111c88a0, and ends in the base destructor at 0x10bee4f0. The class, method and member names are
// invented; the offsets and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10c58410_Base
{
public:
    virtual ~UnkType_10c58410_Base();

    unsigned char unk_4[0x488];
};

class UnkType_10929a90
{
public:
    ~UnkType_10929a90()
    {
        Unk_10929a90(0, unk_4, 4);
        if ( unk_0 != 0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_8 = 0;
        unk_4 = 0;
    }

    void Unk_10929a90(int Index, int Count, int Size);

    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10c57610
{
public:
    ~UnkType_10c57610()
    {
        Unk_10c57610(0, unk_4, 8);
        if ( unk_0 != 0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_8 = 0;
        unk_4 = 0;
    }

    void Unk_10c57610(int Index, int Count, int Size);

    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10c58410 : public UnkType_10c58410_Base
{
public:
    virtual ~UnkType_10c58410();
    void Unk_10cd7a30();

    UnkType_10929a90 unk_48c;
    unsigned char unk_498[0x24];
    UnkType_10c57610 unk_4bc;
};

// UnkType_10c58410::~UnkType_10c58410
UnkType_10c58410::~UnkType_10c58410()
{
    Unk_10cd7a30();
}
