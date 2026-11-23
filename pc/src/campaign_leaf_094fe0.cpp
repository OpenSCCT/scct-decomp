// campaign_leaf_094fe0.cpp -- virtual destructor at VA 0x10994fe0 (vtable at VA 0x110c7708): calls
// the method at VA 0x10cd7a30, destroys the dynamic array at 0x2b4 (method at VA 0x10991ed0 with 0,
// its count and the element size 4, then frees its data through virtual slot 2 of the allocator
// global at VA 0x111c88a0) and ends in the base class destructor at VA 0x1092ad20. The class,
// member and method names are invented; the offsets and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10994fe0_Base
{
public:
    virtual ~UnkType_10994fe0_Base();
    void Unk_10cd7a30();

private:
    unsigned char unk_04[0x2b4 - 0x04];
};

class UnkType_10994fe0_Array
{
public:
    ~UnkType_10994fe0_Array()
    {
        Unk_10991ed0(0, unk_04, 4);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10991ed0(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10994fe0 : public UnkType_10994fe0_Base
{
public:
    virtual ~UnkType_10994fe0();

private:
    UnkType_10994fe0_Array unk_2b4;
};

// UnkType_10994fe0::~UnkType_10994fe0
UnkType_10994fe0::~UnkType_10994fe0()
{
    Unk_10cd7a30();
}
