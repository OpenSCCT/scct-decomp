// campaign_leaf_3068f0.cpp -- one function at file offset 0x3068f0, preferred VA 0x10c068f0. A
// destructor: it installs the vtable at 0x110cbac0, calls the method at 0x10cd7a30, destroys the
// array at 0x2b4 (removing its 4-byte elements with the method at 0x109a5e50 and freeing its data
// through the allocator at 0x111c88a0) and ends in the base destructor at 0x1092ad20. The class,
// method and member names are invented; the offsets and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10c068f0_Base
{
public:
    virtual ~UnkType_10c068f0_Base();

    unsigned char unk_4[0x2b0];
};

class UnkType_109a5e50
{
public:
    ~UnkType_109a5e50()
    {
        Unk_109a5e50(0, unk_4, 4);
        if ( unk_0 != 0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_8 = 0;
        unk_4 = 0;
    }

    void Unk_109a5e50(int Index, int Count, int Size);

    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10c068f0 : public UnkType_10c068f0_Base
{
public:
    virtual ~UnkType_10c068f0();
    void Unk_10cd7a30();

    UnkType_109a5e50 unk_2b4;
};

// UnkType_10c068f0::~UnkType_10c068f0
UnkType_10c068f0::~UnkType_10c068f0()
{
    Unk_10cd7a30();
}
