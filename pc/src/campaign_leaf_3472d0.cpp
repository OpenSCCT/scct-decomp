// campaign_leaf_3472d0.cpp -- one function at file offset 0x3472d0, preferred VA 0x10c472d0. A
// destructor: it installs the vtable at 0x111006c0, calls the method at 0x10cd7a30, destroys 0x450
// (removing its 1-byte elements with the method at 0x10966210) and 0x444 (removing its 1-byte
// elements with the method at 0x10966210) and 0x438 (removing its 4-byte elements with the method
// at 0x10c46510) and 0x428 (removing its 4-byte elements with the method at 0x10c46510) and 0x410
// (removing its 0xc-byte elements with the method at 0x10c46480) and 0x400 (removing its 0x18-byte
// elements with the method at 0x10c463f0), freeing their data through the allocator at 0x111c88a0,
// and ends in the base destructor at 0x10bee4f0. The class, method and member names are invented;
// the offsets and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10c472d0_Base
{
public:
    virtual ~UnkType_10c472d0_Base();

    unsigned char unk_4[0x3fc];
};

class UnkType_10c463f0
{
public:
    ~UnkType_10c463f0()
    {
        Unk_10c463f0(0, unk_4, 0x18);
        if ( unk_0 != 0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_8 = 0;
        unk_4 = 0;
    }

    void Unk_10c463f0(int Index, int Count, int Size);

    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10c46480
{
public:
    ~UnkType_10c46480()
    {
        Unk_10c46480(0, unk_4, 0xc);
        if ( unk_0 != 0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_8 = 0;
        unk_4 = 0;
    }

    void Unk_10c46480(int Index, int Count, int Size);

    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10c46510
{
public:
    ~UnkType_10c46510()
    {
        Unk_10c46510(0, unk_4, 4);
        if ( unk_0 != 0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_8 = 0;
        unk_4 = 0;
    }

    void Unk_10c46510(int Index, int Count, int Size);

    void* unk_0;
    int unk_4;
    int unk_8;
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

class UnkType_10c472d0 : public UnkType_10c472d0_Base
{
public:
    virtual ~UnkType_10c472d0();
    void Unk_10cd7a30();

    UnkType_10c463f0 unk_400;
    unsigned char unk_40c[0x4];
    UnkType_10c46480 unk_410;
    unsigned char unk_41c[0xc];
    UnkType_10c46510 unk_428;
    unsigned char unk_434[0x4];
    UnkType_10c46510 unk_438;
    UnkType_10966210 unk_444;
    UnkType_10966210 unk_450;
};

// UnkType_10c472d0::~UnkType_10c472d0
UnkType_10c472d0::~UnkType_10c472d0()
{
    Unk_10cd7a30();
}
