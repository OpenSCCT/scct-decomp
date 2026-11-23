// campaign_leaf_0c80e0.cpp -- virtual destructor at VA 0x109c80e0 (vtable at VA 0x110cf0b8): calls
// the method at VA 0x10cd7a30, then destroys the dynamic array at 0x2c4 (method at VA 0x10929a90,
// element size 4), the dynamic array at 0x2b8 (method at VA 0x109c7b30, element size 32); each
// array is passed 0 and its count, then its data is freed through virtual slot 2 of the allocator
// global at VA 0x111c88a0; it ends in the outermost base destructor at VA 0x1092ad20. The class,
// member and method names are invented; the offsets and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_109c80e0_Array1
{
public:
    ~UnkType_109c80e0_Array1()
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

class UnkType_109c80e0_Array2
{
public:
    ~UnkType_109c80e0_Array2()
    {
        Unk_109c7b30(0, unk_04, 32);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_109c7b30(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109c80e0_Base
{
public:
    virtual ~UnkType_109c80e0_Base();
    void Unk_10cd7a30();

private:
    unsigned char unk_04[0x2b8 - 0x04];
};

class UnkType_109c80e0 : public UnkType_109c80e0_Base
{
public:
    virtual ~UnkType_109c80e0();

private:
    UnkType_109c80e0_Array2 unk_2b8;
    UnkType_109c80e0_Array1 unk_2c4;
};

// UnkType_109c80e0::~UnkType_109c80e0
UnkType_109c80e0::~UnkType_109c80e0()
{
    Unk_10cd7a30();
}
