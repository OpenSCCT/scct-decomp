// campaign_leaf_2f1450.cpp -- destructor at VA 0x10bf1450 of a class with a vtable (VA 0x110ee7b0):
// calls the method at VA 0x10cd7a30, then destroys the dynamic arrays at 0x45c and 0x450 (contents
// removed through the methods at VA 0x10929b20 and VA 0x10929b20, element size 4 and 4; data freed
// through virtual slot 2 of the allocator at VA 0x111c88a0; three words cleared), and runs the base
// class destructor at VA 0x10bee4f0. The class, member and method names are invented; the offsets
// and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10bf1450_Base
{
public:
    virtual ~UnkType_10bf1450_Base();

    void Unk_10cd7a30();

private:
    unsigned char unk_04[0x3fc - 0x04];
};

class UnkType_10bf1450_450
{
public:
    ~UnkType_10bf1450_450()
    {
        Unk_10929b20(0, unk_04, 4);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10929b20(int Index, int Count, int ElementSize);

    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10bf1450_45c
{
public:
    ~UnkType_10bf1450_45c()
    {
        Unk_10929b20(0, unk_04, 4);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10929b20(int Index, int Count, int ElementSize);

    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10bf1450 : public UnkType_10bf1450_Base
{
public:
    virtual ~UnkType_10bf1450();

private:
    unsigned char unk_3fc[0x450 - 0x3fc];
    UnkType_10bf1450_450 unk_450;
    UnkType_10bf1450_45c unk_45c;
};

// UnkType_10bf1450::~UnkType_10bf1450
UnkType_10bf1450::~UnkType_10bf1450()
{
    Unk_10cd7a30();
}
