// campaign_leaf_374360.cpp -- one function at file offset 0x374360, preferred VA 0x10c74360. A
// destructor: it installs the vtable at 0x1110f990, calls the method at 0x10cd7a30, destroys 0x27c
// (removing its 4-byte elements with the method at 0x10929170) and 0x270 (removing its 0x40-byte
// elements with the method at 0x10c72530) and 0x264 (emptying it with the method at 0x10c73b50) and
// 0x258 (removing its 0x28-byte elements with the method at 0x10c72410) and 0x24c (removing its
// 0x3c-byte elements with the method at 0x10c72380) and 0x234 (removing its 2-byte elements with
// the method at 0x10907710) and 0x210 (removing its 0x1c-byte elements with the method at
// 0x10a54a40), freeing their data through the allocator at 0x111c88a0, and ends in the base
// destructor at 0x10a53b70. The class, method and member names are invented; the offsets and the
// bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10c74360_Base
{
public:
    virtual ~UnkType_10c74360_Base();

    unsigned char unk_4[0x20c];
};

class UnkType_10a54a40
{
public:
    ~UnkType_10a54a40()
    {
        Unk_10a54a40(0, unk_4, 0x1c);
        if ( unk_0 != 0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_8 = 0;
        unk_4 = 0;
    }

    void Unk_10a54a40(int Index, int Count, int Size);

    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10907710
{
public:
    // UnkType_10907710::~UnkType_10907710
    ~UnkType_10907710()
    {
        Unk_10907710(0, unk_4, 2);
        if ( unk_0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_4 = unk_8 = 0;
    }

    // UnkType_10907710::Empty
    void Empty(int Slack = 0)
    {
        unk_4 = 0;
        unk_8 = Slack;
        unk_0 = (unsigned short*)GUnk_111c88a0->Realloc(unk_0, unk_8 * 2, L"FArray::_WORD");
    }

    void Unk_10907710(int Index, int Count, int ElementSize);

private:
    unsigned short* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10c72380
{
public:
    ~UnkType_10c72380()
    {
        Unk_10c72380(0, unk_4, 0x3c);
        if ( unk_0 != 0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_8 = 0;
        unk_4 = 0;
    }

    void Unk_10c72380(int Index, int Count, int Size);

    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10c72410
{
public:
    ~UnkType_10c72410()
    {
        Unk_10c72410(0, unk_4, 0x28);
        if ( unk_0 != 0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_8 = 0;
        unk_4 = 0;
    }

    void Unk_10c72410(int Index, int Count, int Size);

    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10c74360_10c73b50
{
public:
    ~UnkType_10c74360_10c73b50()
    {
        Unk_10c73b50(0, unk_4);
        if ( unk_0 != 0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_8 = 0;
        unk_4 = 0;
    }

    void Unk_10c73b50(int Index, int Count);

    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10c72530
{
public:
    ~UnkType_10c72530()
    {
        Unk_10c72530(0, unk_4, 0x40);
        if ( unk_0 != 0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_8 = 0;
        unk_4 = 0;
    }

    void Unk_10c72530(int Index, int Count, int Size);

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

class UnkType_10c74360 : public UnkType_10c74360_Base
{
public:
    virtual ~UnkType_10c74360();
    void Unk_10cd7a30();

    UnkType_10a54a40 unk_210;
    unsigned char unk_21c[0x18];
    UnkType_10907710 unk_234;
    unsigned char unk_240[0xc];
    UnkType_10c72380 unk_24c;
    UnkType_10c72410 unk_258;
    UnkType_10c74360_10c73b50 unk_264;
    UnkType_10c72530 unk_270;
    UnkType_10929170 unk_27c;
};

// UnkType_10c74360::~UnkType_10c74360
UnkType_10c74360::~UnkType_10c74360()
{
    Unk_10cd7a30();
}
