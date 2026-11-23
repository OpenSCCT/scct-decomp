// campaign_leaf_0a4200.cpp -- virtual destructor at VA 0x109a4200 (vtable at VA 0x110cb3c8): calls
// the method at VA 0x10cd7a30, destroys the dynamic array at 0x2c0 (method at VA 0x10929a90 with 0,
// its count and the element size 4, then frees its data through virtual slot 2 of the allocator
// global at VA 0x111c88a0), then the member at 0x2b4 (destructor at VA 0x1090ba70), and ends in the
// base class destructor at VA 0x1092ad20. The class, member and method names are invented; the
// offsets and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_109a4200_Base
{
public:
    virtual ~UnkType_109a4200_Base();
    void Unk_10cd7a30();

private:
    unsigned char unk_04[0x2b4 - 0x04];
};

class UnkType_109a4200_Member
{
public:
    ~UnkType_109a4200_Member();

private:
    unsigned char unk_00[0x0c];
};

class UnkType_109a4200_Array
{
public:
    ~UnkType_109a4200_Array()
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

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109a4200 : public UnkType_109a4200_Base
{
public:
    virtual ~UnkType_109a4200();

private:
    UnkType_109a4200_Member unk_2b4;
    UnkType_109a4200_Array unk_2c0;
};

// UnkType_109a4200::~UnkType_109a4200
UnkType_109a4200::~UnkType_109a4200()
{
    Unk_10cd7a30();
}
