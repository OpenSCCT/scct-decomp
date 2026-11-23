// campaign_leaf_3263b0.cpp -- one function at file offset 0x3263b0, preferred VA 0x10c263b0. A
// destructor: it installs the vtable at 0x110f9458, calls the method at 0x10cd7a30, destroys the
// arrays at 0x34 (removing its 8-byte elements with the method at 0x10c25ac0) and 0x28 (removing
// its elements with the method at 0x10c25fe0), freeing their data through the allocator at
// 0x111c88a0, and ends in the base destructor at 0x10cdc460. The class, method and member names
// are invented; the offsets and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10c263b0_Base
{
public:
    virtual ~UnkType_10c263b0_Base();

    unsigned char unk_4[0x24];
};

class UnkType_10c25fe0
{
public:
    ~UnkType_10c25fe0()
    {
        Unk_10c25fe0(0, unk_4);
        if ( unk_0 != 0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_8 = 0;
        unk_4 = 0;
    }

    void Unk_10c25a30(int Index, int Count, int Size);
    void Unk_10c25fe0(int Index, int Count);

    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10c25ac0
{
public:
    ~UnkType_10c25ac0()
    {
        Unk_10c25ac0(0, unk_4, 8);
        if ( unk_0 != 0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_8 = 0;
        unk_4 = 0;
    }

    void Unk_10c25ac0(int Index, int Count, int Size);

    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10c263b0 : public UnkType_10c263b0_Base
{
public:
    virtual ~UnkType_10c263b0();
    void Unk_10cd7a30();

    UnkType_10c25fe0 unk_28;
    UnkType_10c25ac0 unk_34;
};

// UnkType_10c263b0::~UnkType_10c263b0
UnkType_10c263b0::~UnkType_10c263b0()
{
    Unk_10cd7a30();
}
