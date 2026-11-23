// campaign_leaf_32aa70.cpp -- one function at file offset 0x32aa70, preferred VA 0x10c2aa70. A
// destructor: it installs the vtable at 0x110f9938, calls the method at 0x10cd7a30, destroys the
// member at 0xe0 (destructor at 0x1090ba70) and 0xd4 (emptying it with the method at 0x10c29e50)
// and 0xc8 (emptying it with the method at 0x10b2e980) and 0xb8 (emptying it with the method at
// 0x10b2e7f0) and 0xa8 (emptying it with the method at 0x10b2e620) and 0x94 (removing its 4-byte
// elements with the method at 0x10929170) and 0x88 (removing its 8-byte elements with the method at
// 0x10c28560) and the member at 0x78 (destructor at 0x1090ba70), freeing their data through the
// allocator at 0x111c88a0, and ends in the base destructor at 0x10cdc460. The class, method and
// member names are invented; the offsets and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10c2aa70_Base
{
public:
    virtual ~UnkType_10c2aa70_Base();

    unsigned char unk_4[0x74];
};

class UnkType_1090ba70
{
public:
    ~UnkType_1090ba70();

private:
    int unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10c28560
{
public:
    ~UnkType_10c28560()
    {
        Unk_10c28560(0, unk_4, 8);
        if ( unk_0 != 0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_8 = 0;
        unk_4 = 0;
    }

    void Unk_10c28560(int Index, int Count, int Size);

    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10929170
{
public:
    ~UnkType_10929170()
    {
        Unk_10929170(0, unk_4, 4);
        if ( unk_0 != 0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_8 = 0;
        unk_4 = 0;
    }

    void Unk_10929170(int Index, int Count, int Size);

    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10b2e620
{
public:
    ~UnkType_10b2e620()
    {
        Unk_10b2e620(0, unk_4);
        if ( unk_0 != 0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_8 = 0;
        unk_4 = 0;
    }

    void Unk_10b2e620(int Index, int Count);

    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10b2e7f0
{
public:
    ~UnkType_10b2e7f0()
    {
        Unk_10b2e7f0(0, unk_4);
        if ( unk_0 != 0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_8 = 0;
        unk_4 = 0;
    }

    void Unk_10b2e7f0(int Index, int Count);

    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10b2e980
{
public:
    ~UnkType_10b2e980()
    {
        Unk_10b2e980(0, unk_4);
        if ( unk_0 != 0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_8 = 0;
        unk_4 = 0;
    }

    void Unk_10b2e980(int Index, int Count);

    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10c2aa70_10c29e50
{
public:
    ~UnkType_10c2aa70_10c29e50()
    {
        Unk_10c29e50(0, unk_4);
        if ( unk_0 != 0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_8 = 0;
        unk_4 = 0;
    }

    void Unk_10c29e50(int Index, int Count);

    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10c2aa70 : public UnkType_10c2aa70_Base
{
public:
    virtual ~UnkType_10c2aa70();
    void Unk_10cd7a30();

    UnkType_1090ba70 unk_78;
    unsigned char unk_84[0x4];
    UnkType_10c28560 unk_88;
    UnkType_10929170 unk_94;
    unsigned char unk_a0[0x8];
    UnkType_10b2e620 unk_a8;
    unsigned char unk_b4[0x4];
    UnkType_10b2e7f0 unk_b8;
    unsigned char unk_c4[0x4];
    UnkType_10b2e980 unk_c8;
    UnkType_10c2aa70_10c29e50 unk_d4;
    UnkType_1090ba70 unk_e0;
};

// UnkType_10c2aa70::~UnkType_10c2aa70
UnkType_10c2aa70::~UnkType_10c2aa70()
{
    Unk_10cd7a30();
}
