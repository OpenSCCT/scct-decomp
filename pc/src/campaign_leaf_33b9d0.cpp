// campaign_leaf_33b9d0.cpp -- one function at file offset 0x33b9d0, preferred VA 0x10c3b9d0. A
// destructor: it installs the vtable at 0x110fd770, calls the method at 0x10cd7a30, destroys the
// arrays at 0x41c (removing its 0x20-byte elements with the method at 0x10c3b830) and 0x410
// (removing its 4-byte elements with the method at 0x10919a00) and 0x404 (removing its 4-byte
// elements with the method at 0x10919a00), freeing their data through the allocator at 0x111c88a0,
// and ends in the base destructor at 0x10bee4f0. The class, method and member names are invented;
// the offsets and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10c3b9d0_Base
{
public:
    virtual ~UnkType_10c3b9d0_Base();

    unsigned char unk_4[0x400];
};

class UnkType_10919a00
{
public:
    ~UnkType_10919a00()
    {
        Unk_10919a00(0, unk_4, 4);
        if ( unk_0 != 0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_8 = 0;
        unk_4 = 0;
    }

    void Unk_10919a00(int Index, int Count, int Size);

    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10c3b830
{
public:
    ~UnkType_10c3b830()
    {
        Unk_10c3b830(0, unk_4, 0x20);
        if ( unk_0 != 0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_8 = 0;
        unk_4 = 0;
    }

    void Unk_10c3b830(int Index, int Count, int Size);

    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10c3b9d0 : public UnkType_10c3b9d0_Base
{
public:
    virtual ~UnkType_10c3b9d0();
    void Unk_10cd7a30();

    UnkType_10919a00 unk_404;
    UnkType_10919a00 unk_410;
    UnkType_10c3b830 unk_41c;
};

// UnkType_10c3b9d0::~UnkType_10c3b9d0
UnkType_10c3b9d0::~UnkType_10c3b9d0()
{
    Unk_10cd7a30();
}
