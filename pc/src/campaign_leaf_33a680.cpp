// campaign_leaf_33a680.cpp -- one function at file offset 0x33a680, preferred VA 0x10c3a680. A
// destructor: it installs the vtable at 0x110ef388, calls the method at 0x10cd7a30, destroys the
// array at 0x3fc (removing its 0xc-byte elements with the method at 0x10bf3270 and freeing its data
// through the allocator at 0x111c88a0) and ends in the base destructor at 0x10bee4f0. The class,
// method and member names are invented; the offsets and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10c3a680_Base
{
public:
    virtual ~UnkType_10c3a680_Base();

    unsigned char unk_4[0x3f8];
};

class UnkType_10bf3270
{
public:
    ~UnkType_10bf3270()
    {
        Unk_10bf3270(0, unk_4, 0xc);
        if ( unk_0 != 0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_8 = 0;
        unk_4 = 0;
    }

    void Unk_10bf3270(int Index, int Count, int Size);

    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10c3a680 : public UnkType_10c3a680_Base
{
public:
    virtual ~UnkType_10c3a680();
    void Unk_10cd7a30();

    UnkType_10bf3270 unk_3fc;
};

// UnkType_10c3a680::~UnkType_10c3a680
UnkType_10c3a680::~UnkType_10c3a680()
{
    Unk_10cd7a30();
}
