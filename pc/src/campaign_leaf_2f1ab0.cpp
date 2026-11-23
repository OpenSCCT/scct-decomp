// campaign_leaf_2f1ab0.cpp -- destructor at VA 0x10bf1ab0 of a class with a vtable (VA 0x110eed90):
// calls the method at VA 0x10cd7a30, then destroys the dynamic arrays at 0x408 and 0x3fc (contents
// removed through the methods at VA 0x10be5ed0 and VA 0x10929a90, element size 4 and 4; data freed
// through virtual slot 2 of the allocator at VA 0x111c88a0; three words cleared), and runs the base
// class destructor at VA 0x10bee4f0. The class, member and method names are invented; the offsets
// and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10bf1ab0_Base
{
public:
    virtual ~UnkType_10bf1ab0_Base();

    void Unk_10cd7a30();

private:
    unsigned char unk_04[0x3fc - 0x04];
};

class UnkType_10bf1ab0_3fc
{
public:
    ~UnkType_10bf1ab0_3fc()
    {
        Unk_10929a90(0, unk_04, 4);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10929a90(int Index, int Count, int ElementSize);

    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10bf1ab0_408
{
public:
    ~UnkType_10bf1ab0_408()
    {
        Unk_10be5ed0(0, unk_04, 4);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10be5ed0(int Index, int Count, int ElementSize);

    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10bf1ab0 : public UnkType_10bf1ab0_Base
{
public:
    virtual ~UnkType_10bf1ab0();

private:
    UnkType_10bf1ab0_3fc unk_3fc;
    UnkType_10bf1ab0_408 unk_408;
};

// UnkType_10bf1ab0::~UnkType_10bf1ab0
UnkType_10bf1ab0::~UnkType_10bf1ab0()
{
    Unk_10cd7a30();
}
