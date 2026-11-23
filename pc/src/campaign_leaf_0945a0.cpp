// campaign_leaf_0945a0.cpp -- virtual destructor at VA 0x109945a0 (vtable at VA 0x110c4f08): calls
// the method at VA 0x10cd7a30, then destroys the dynamic array at 0x364 (method at VA 0x10991b70,
// element size 4), the dynamic array at 0x358 (method at VA 0x10929a90, element size 4); then the
// inline destructor of base class 1 (vtable at VA 0x110c4728) calls it, then destroys the member at
// 0x34c (destructor at VA 0x1090ba70); then the inline destructor of base class 2 (vtable at VA
// 0x110c4470) calls it; each array is passed 0 and its count, then its data is freed through
// virtual slot 2 of the allocator global at VA 0x111c88a0; it ends in the outermost base destructor
// at VA 0x1092ad20. The class, member and method names are invented; the offsets and the addresses
// are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_109945a0_Array1
{
public:
    ~UnkType_109945a0_Array1()
    {
        Unk_10991b70(0, unk_04, 4);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10991b70(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109945a0_Array2
{
public:
    ~UnkType_109945a0_Array2()
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

class UnkType_109945a0_Member
{
public:
    ~UnkType_109945a0_Member();

private:
    unsigned char unk_00[0x0c];
};

class UnkType_109945a0_Base
{
public:
    virtual ~UnkType_109945a0_Base();
    void Unk_10cd7a30();

private:
    unsigned char unk_04[0x34c - 0x04];
};

class UnkType_109945a0_Level2 : public UnkType_109945a0_Base
{
public:
    virtual ~UnkType_109945a0_Level2()
    {
        Unk_10cd7a30();
    }
};

class UnkType_109945a0_Level1 : public UnkType_109945a0_Level2
{
public:
    virtual ~UnkType_109945a0_Level1()
    {
        Unk_10cd7a30();
    }

private:
    UnkType_109945a0_Member unk_34c;
};

class UnkType_109945a0 : public UnkType_109945a0_Level1
{
public:
    virtual ~UnkType_109945a0();

private:
    UnkType_109945a0_Array2 unk_358;
    UnkType_109945a0_Array1 unk_364;
};

// UnkType_109945a0::~UnkType_109945a0
UnkType_109945a0::~UnkType_109945a0()
{
    Unk_10cd7a30();
}
