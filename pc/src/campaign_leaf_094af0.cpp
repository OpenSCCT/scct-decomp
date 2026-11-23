// campaign_leaf_094af0.cpp -- virtual destructor at VA 0x10994af0 (vtable at VA 0x110c64c8): calls
// the method at VA 0x10cd7a30, destroys the member at 0x2f0 (destructor at VA 0x1090ba70), the
// dynamic array at 0x2e0 (method at VA 0x10991c00 with 0, its count and the element size 4, then
// frees its data through virtual slot 2 of the allocator global at VA 0x111c88a0) and the member at
// 0x2b4; then the inline destructor of its base class (vtable at VA 0x110c6230) calls the same
// method, and it ends in the outermost base destructor at VA 0x1092ad20. The class, member and
// method names are invented; the offsets and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10994af0_Member
{
public:
    ~UnkType_10994af0_Member();

private:
    unsigned char unk_00[0x0c];
};

class UnkType_10994af0_Base
{
public:
    virtual ~UnkType_10994af0_Base();
    void Unk_10cd7a30();

private:
    unsigned char unk_04[0x2b4 - 0x04];
};

class UnkType_10994af0_Level1 : public UnkType_10994af0_Base
{
public:
    virtual ~UnkType_10994af0_Level1()
    {
        Unk_10cd7a30();
    }
};

class UnkType_10994af0_Array
{
public:
    ~UnkType_10994af0_Array()
    {
        Unk_10991c00(0, unk_04, 4);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10991c00(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10994af0 : public UnkType_10994af0_Level1
{
public:
    virtual ~UnkType_10994af0();

private:
    UnkType_10994af0_Member unk_2b4;
    unsigned char unk_2c0[0x2e0 - 0x2c0];
    UnkType_10994af0_Array unk_2e0;
    unsigned char unk_2ec[0x2f0 - 0x2ec];
    UnkType_10994af0_Member unk_2f0;
};

// UnkType_10994af0::~UnkType_10994af0
UnkType_10994af0::~UnkType_10994af0()
{
    Unk_10cd7a30();
}
