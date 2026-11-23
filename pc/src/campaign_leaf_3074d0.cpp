// campaign_leaf_3074d0.cpp -- one function at file offset 0x3074d0, preferred VA 0x10c074d0. A
// destructor: it installs the vtable at 0x110f5ca8, calls the method at 0x10cd7a30, destroys the
// arrays at 0x448 (removing its 4-byte elements with the method at 0x10929a90) and 0x2b8 (removing
// its 4-byte elements with the method at 0x10bdb4e0), freeing their data through the allocator at
// 0x111c88a0, and ends in the base destructor at 0x1092ad20. The class, method and member names are
// invented; the offsets and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10c074d0_Base
{
public:
    virtual ~UnkType_10c074d0_Base();

    unsigned char unk_4[0x2b4];
};

class UnkType_10bdb4e0
{
public:
    ~UnkType_10bdb4e0()
    {
        Unk_10bdb4e0(0, unk_4, 4);
        if ( unk_0 != 0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_8 = 0;
        unk_4 = 0;
    }

    void Unk_10bdb4e0(int Index, int Count, int Size);

    void* unk_0;
    int unk_4;
    int unk_8;
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

class UnkType_10c074d0 : public UnkType_10c074d0_Base
{
public:
    virtual ~UnkType_10c074d0();
    void Unk_10cd7a30();

    UnkType_10bdb4e0 unk_2b8;
    unsigned char unk_2c4[0x184];
    UnkType_10929a90 unk_448;
};

// UnkType_10c074d0::~UnkType_10c074d0
UnkType_10c074d0::~UnkType_10c074d0()
{
    Unk_10cd7a30();
}
