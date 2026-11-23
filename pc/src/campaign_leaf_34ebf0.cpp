// campaign_leaf_34ebf0.cpp -- one function at file offset 0x34ebf0, preferred VA 0x10c4ebf0. A
// destructor: it installs the vtable at 0x111027f8, calls the method at 0x10cd7a30, destroys the
// arrays at 0x43c (removing its 1-byte elements with the method at 0x10966210) and 0x430 (removing
// its 1-byte elements with the method at 0x10966210), freeing their data through the allocator at
// 0x111c88a0, and ends in the base destructor at 0x10c3a680. The class, method and member names are
// invented; the offsets and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10c4ebf0_Base
{
public:
    virtual ~UnkType_10c4ebf0_Base();

    unsigned char unk_4[0x42c];
};

class UnkType_10966210
{
public:
    ~UnkType_10966210()
    {
        Unk_10966210(0, unk_4, 1);
        if ( unk_0 != 0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_8 = 0;
        unk_4 = 0;
    }

    void Unk_10966210(int Index, int Count, int Size);

    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10c4ebf0 : public UnkType_10c4ebf0_Base
{
public:
    virtual ~UnkType_10c4ebf0();
    void Unk_10cd7a30();

    UnkType_10966210 unk_430;
    UnkType_10966210 unk_43c;
};

// UnkType_10c4ebf0::~UnkType_10c4ebf0
UnkType_10c4ebf0::~UnkType_10c4ebf0()
{
    Unk_10cd7a30();
}
