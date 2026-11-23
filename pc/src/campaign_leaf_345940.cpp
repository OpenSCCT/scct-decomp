// campaign_leaf_345940.cpp -- one function at file offset 0x345940, preferred VA 0x10c45940. A
// destructor: it installs the vtable at 0x11100180, calls the method at 0x10cd7a30, destroys the
// arrays at 0x410 (removing its 4-byte elements with the method at 0x109beb60) and 0x404 (removing
// its 4-byte elements with the method at 0x10bec6b0), freeing their data through the allocator at
// 0x111c88a0, and ends in the base destructor at 0x10bee4f0. The class, method and member names are
// invented; the offsets and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10c45940_Base
{
public:
    virtual ~UnkType_10c45940_Base();

    unsigned char unk_4[0x400];
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

class UnkType_109beb60
{
public:
    ~UnkType_109beb60()
    {
        Unk_109beb60(0, unk_4, 4);
        if ( unk_0 != 0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_8 = 0;
        unk_4 = 0;
    }

    void Unk_109beb60(int Index, int Count, int Size);

    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10c45940 : public UnkType_10c45940_Base
{
public:
    virtual ~UnkType_10c45940();
    void Unk_10cd7a30();

    UnkType_10bec6b0 unk_404;
    UnkType_109beb60 unk_410;
};

// UnkType_10c45940::~UnkType_10c45940
UnkType_10c45940::~UnkType_10c45940()
{
    Unk_10cd7a30();
}
