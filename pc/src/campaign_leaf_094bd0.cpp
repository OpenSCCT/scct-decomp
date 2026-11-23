// campaign_leaf_094bd0.cpp -- virtual destructor at VA 0x10994bd0 (vtable at VA 0x110c6a00): calls
// the method at VA 0x10cd7a30, then destroys the dynamic array at 0x39c (method at VA 0x10929b20,
// element size 4), the dynamic array at 0x36c (method at VA 0x10991ae0, element size 4), the
// dynamic array at 0x360 (method at VA 0x10991ae0, element size 4), the dynamic array at 0x354
// (method at VA 0x10929b20, element size 4), the dynamic array at 0x348 (method at VA 0x10929b20,
// element size 4), the dynamic array at 0x2dc (method at VA 0x10991d20, element size 4), the
// dynamic array at 0x2d0 (method at VA 0x10991c90, element size 4), the dynamic array at 0x2c4
// (method at VA 0x10929a90, element size 4); then the inline destructor of base class 1 (vtable at
// VA 0x110c6230) calls it; each array is passed 0 and its count, then its data is freed through
// virtual slot 2 of the allocator global at VA 0x111c88a0; it ends in the outermost base destructor
// at VA 0x1092ad20. The class, member and method names are invented; the offsets and the addresses
// are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10994bd0_Array1
{
public:
    ~UnkType_10994bd0_Array1()
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

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10994bd0_Array2
{
public:
    ~UnkType_10994bd0_Array2()
    {
        Unk_10991ae0(0, unk_04, 4);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10991ae0(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10994bd0_Array3
{
public:
    ~UnkType_10994bd0_Array3()
    {
        Unk_10991d20(0, unk_04, 4);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10991d20(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10994bd0_Array4
{
public:
    ~UnkType_10994bd0_Array4()
    {
        Unk_10991c90(0, unk_04, 4);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10991c90(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10994bd0_Array5
{
public:
    ~UnkType_10994bd0_Array5()
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

class UnkType_10994bd0_Base
{
public:
    virtual ~UnkType_10994bd0_Base();
    void Unk_10cd7a30();

private:
    unsigned char unk_04[0x2c4 - 0x04];
};

class UnkType_10994bd0_Level1 : public UnkType_10994bd0_Base
{
public:
    virtual ~UnkType_10994bd0_Level1()
    {
        Unk_10cd7a30();
    }
};

class UnkType_10994bd0 : public UnkType_10994bd0_Level1
{
public:
    virtual ~UnkType_10994bd0();

private:
    UnkType_10994bd0_Array5 unk_2c4;
    UnkType_10994bd0_Array4 unk_2d0;
    UnkType_10994bd0_Array3 unk_2dc;
    unsigned char unk_2e8[0x348 - 0x2e8];
    UnkType_10994bd0_Array1 unk_348;
    UnkType_10994bd0_Array1 unk_354;
    UnkType_10994bd0_Array2 unk_360;
    UnkType_10994bd0_Array2 unk_36c;
    unsigned char unk_378[0x39c - 0x378];
    UnkType_10994bd0_Array1 unk_39c;
};

// UnkType_10994bd0::~UnkType_10994bd0
UnkType_10994bd0::~UnkType_10994bd0()
{
    Unk_10cd7a30();
}
