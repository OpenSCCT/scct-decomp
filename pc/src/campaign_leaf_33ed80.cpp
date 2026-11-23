// campaign_leaf_33ed80.cpp -- one function at file offset 0x33ed80, preferred VA 0x10c3ed80. A
// destructor: it installs the vtable at 0x110fe718, calls the method at 0x10cd7a30, destroys the
// arrays at 0x720 (removing its 4-byte elements with the method at 0x10bec6b0) and 0x6bc (removing
// its 0x20-byte elements with the method at 0x10c3e3f0), freeing their data through the allocator
// at 0x111c88a0, and ends in the base destructor at 0x10bee4f0. The class, method and member names
// are invented; the offsets and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10c3ed80_Base
{
public:
    virtual ~UnkType_10c3ed80_Base();

    unsigned char unk_4[0x6b8];
};

class UnkType_10c3e3f0
{
public:
    ~UnkType_10c3e3f0()
    {
        Unk_10c3e3f0(0, unk_4, 0x20);
        if ( unk_0 != 0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_8 = 0;
        unk_4 = 0;
    }

    void Unk_10c3e3f0(int Index, int Count, int Size);

    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10bec6b0
{
public:
    ~UnkType_10bec6b0()
    {
        Unk_10bec6b0(0, unk_4, 4);
        if ( unk_0 != 0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_8 = 0;
        unk_4 = 0;
    }

    void Unk_10bec6b0(int Index, int Count, int Size);

    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10c3ed80 : public UnkType_10c3ed80_Base
{
public:
    virtual ~UnkType_10c3ed80();
    void Unk_10cd7a30();

    UnkType_10c3e3f0 unk_6bc;
    unsigned char unk_6c8[0x58];
    UnkType_10bec6b0 unk_720;
};

// UnkType_10c3ed80::~UnkType_10c3ed80
UnkType_10c3ed80::~UnkType_10c3ed80()
{
    Unk_10cd7a30();
}
