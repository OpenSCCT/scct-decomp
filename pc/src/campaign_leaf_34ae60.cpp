// campaign_leaf_34ae60.cpp -- one function at file offset 0x34ae60, preferred VA 0x10c4ae60. A
// destructor: it installs the vtable at 0x111012e0, calls the method at 0x10cd7a30, destroys 0x4b8
// (removing its 4-byte elements with the method at 0x109beb60) and 0x4ac (removing its 4-byte
// elements with the method at 0x109beb60) and 0x4a0 (removing its 4-byte elements with the method
// at 0x109beb60) and the member at 0x46c (destructor at 0x1090ba70) and the member at 0x434
// (destructor at 0x1090ba70) and 0x420 (removing its 4-byte elements with the method at 0x10bec6b0)
// and 0x414 (removing its 4-byte elements with the method at 0x10c4a070), freeing their data
// through the allocator at 0x111c88a0, and ends in the base destructor at 0x10bf1ab0. The class,
// method and member names are invented; the offsets and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10c4ae60_Base
{
public:
    virtual ~UnkType_10c4ae60_Base();

    unsigned char unk_4[0x410];
};

class UnkType_10c4a070
{
public:
    ~UnkType_10c4a070()
    {
        Unk_10c4a070(0, unk_4, 4);
        if ( unk_0 != 0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_8 = 0;
        unk_4 = 0;
    }

    void Unk_10c4a070(int Index, int Count, int Size);

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

class UnkType_1090ba70
{
public:
    ~UnkType_1090ba70();

private:
    int unk_00;
    int unk_04;
    int unk_08;
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

class UnkType_10c4ae60 : public UnkType_10c4ae60_Base
{
public:
    virtual ~UnkType_10c4ae60();
    void Unk_10cd7a30();

    UnkType_10c4a070 unk_414;
    UnkType_10bec6b0 unk_420;
    unsigned char unk_42c[0x8];
    UnkType_1090ba70 unk_434;
    unsigned char unk_440[0x2c];
    UnkType_1090ba70 unk_46c;
    unsigned char unk_478[0x28];
    UnkType_109beb60 unk_4a0;
    UnkType_109beb60 unk_4ac;
    UnkType_109beb60 unk_4b8;
};

// UnkType_10c4ae60::~UnkType_10c4ae60
UnkType_10c4ae60::~UnkType_10c4ae60()
{
    Unk_10cd7a30();
}
