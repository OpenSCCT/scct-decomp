// campaign_leaf_3e5ba0.cpp -- one function at file offset 0x3e5ba0, preferred VA 0x10ce5ba0. A
// destructor: it installs the vtable at 0x11133240, calls the method at 0x10cd7a30, destroys the
// array at 0x50 (removing its 1-byte elements with the method at 0x10966210 and freeing its data
// through the allocator at 0x111c88a0), then runs the intermediate base destructor inline (vtable
// at 0x110cddd8, the method at 0x10cd7a30 again) and ends in the base destructor at 0x10cdc460.
// The class, method and member names are invented; the offsets and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10ce5ba0_Base
{
public:
    virtual ~UnkType_10ce5ba0_Base();
    void Unk_10cd7a30();

    unsigned char unk_4[0x28];
};

class UnkType_10ce5ba0_Middle : public UnkType_10ce5ba0_Base
{
public:
    virtual ~UnkType_10ce5ba0_Middle()
    {
        Unk_10cd7a30();
    }

    unsigned char unk_2c[0x24];
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

class UnkType_10ce5ba0 : public UnkType_10ce5ba0_Middle
{
public:
    virtual ~UnkType_10ce5ba0();

    UnkType_10966210 unk_50;
};

// UnkType_10ce5ba0::~UnkType_10ce5ba0
UnkType_10ce5ba0::~UnkType_10ce5ba0()
{
    Unk_10cd7a30();
}
