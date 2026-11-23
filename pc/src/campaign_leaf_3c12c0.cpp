// campaign_leaf_3c12c0.cpp -- one function at file offset 0x3c12c0, preferred VA 0x10cc12c0. A
// destructor: it installs the vtable at 0x110d6ba0, calls the method at 0x10cd7a30, destroys the
// array at 0x2c (removing its elements with the method at 0x10a46380 and freeing its data through
// the allocator at 0x111c88a0) and ends in the base destructor at 0x10cdc460. The class, method
// and member names are invented; the offsets and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10cc12c0_Base
{
public:
    virtual ~UnkType_10cc12c0_Base();

    unsigned char unk_4[0x28];
};

class UnkType_10a46380
{
public:
    ~UnkType_10a46380()
    {
        Unk_10a46380(0, unk_4, 4);
        if ( unk_0 != 0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_8 = 0;
        unk_4 = 0;
    }

    void Unk_10a46380(int Index, int Count, int Size);

    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10cc12c0 : public UnkType_10cc12c0_Base
{
public:
    virtual ~UnkType_10cc12c0();
    void Unk_10cd7a30();

    UnkType_10a46380 unk_2c;
};

// UnkType_10cc12c0::~UnkType_10cc12c0
UnkType_10cc12c0::~UnkType_10cc12c0()
{
    Unk_10cd7a30();
}
