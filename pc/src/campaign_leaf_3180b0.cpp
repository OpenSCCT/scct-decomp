// campaign_leaf_3180b0.cpp -- one function at file offset 0x3180b0, preferred VA 0x10c180b0. A
// destructor: it installs the vtable at 0x110f8110, calls the method at 0x10cd7a30, destroys the
// array at 0x368 (removing its 8-byte elements with the method at 0x10c17590 and freeing its data
// through the allocator at 0x111c88a0) and ends in the base destructor at 0x10996320. The class,
// method and member names are invented; the offsets and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10c180b0_Base
{
public:
    virtual ~UnkType_10c180b0_Base();

    unsigned char unk_4[0x364];
};

class UnkType_10c17590
{
public:
    ~UnkType_10c17590()
    {
        Unk_10c17590(0, unk_4, 8);
        if ( unk_0 != 0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_8 = 0;
        unk_4 = 0;
    }

    void Unk_10c17590(int Index, int Count, int Size);

    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10c180b0 : public UnkType_10c180b0_Base
{
public:
    virtual ~UnkType_10c180b0();
    void Unk_10cd7a30();

    UnkType_10c17590 unk_368;
};

// UnkType_10c180b0::~UnkType_10c180b0
UnkType_10c180b0::~UnkType_10c180b0()
{
    Unk_10cd7a30();
}
