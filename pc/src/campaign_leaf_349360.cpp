// campaign_leaf_349360.cpp -- one function at file offset 0x349360, preferred VA 0x10c49360. A
// destructor: it installs the vtable at 0x11100f88, calls the method at 0x10cd7a30, destroys the
// arrays at 0x47c (removing its 4-byte elements with the method at 0x109beb60) and 0x430 (removing
// its 4-byte elements with the method at 0x10bec6b0) and 0x424 (removing its 4-byte elements with
// the method at 0x10bec6b0), freeing their data through the allocator at 0x111c88a0, and ends in
// the base destructor at 0x10bee4f0. The class, method and member names are invented; the offsets
// and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10c49360_Base
{
public:
    virtual ~UnkType_10c49360_Base();

    unsigned char unk_4[0x420];
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

class UnkType_10c49360 : public UnkType_10c49360_Base
{
public:
    virtual ~UnkType_10c49360();
    void Unk_10cd7a30();

    UnkType_10bec6b0 unk_424;
    UnkType_10bec6b0 unk_430;
    unsigned char unk_43c[0x40];
    UnkType_109beb60 unk_47c;
};

// UnkType_10c49360::~UnkType_10c49360
UnkType_10c49360::~UnkType_10c49360()
{
    Unk_10cd7a30();
}
