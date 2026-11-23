// campaign_leaf_0c4c50.cpp -- destructor at VA 0x109c4c50: destroys the dynamic arrays at 0x58
// (method at VA 0x109c1960) and 0x4c (method at VA 0x10978750), each passed 0 and its count; then
// the record at 0x38: frees its pointer at 0x0c, clears it and the count at 0x10, and destroys its
// dynamic array at 0x00 (method at VA 0x109bedf0, element size 12); every array's data is freed
// through virtual slot 2 of the allocator global at VA 0x111c88a0. It ends in the base class
// destructor at VA 0x1097b710. The class, member and method names are invented; the offsets and the
// addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_109c4c50_Pairs
{
public:
    ~UnkType_109c4c50_Pairs()
    {
        Unk_109bedf0(0, unk_04, 12);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_109bedf0(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109c4c50_Table
{
public:
    ~UnkType_109c4c50_Table()
    {
        if ( unk_0c )
        {
            GUnk_111c88a0->Free(unk_0c);
        }
        unk_0c = 0;
        unk_10 = 0;
    }

private:
    UnkType_109c4c50_Pairs unk_00;
    void* unk_0c;
    int unk_10;
};

class UnkType_109c4c50_Array1
{
public:
    ~UnkType_109c4c50_Array1()
    {
        Unk_10978750(0, unk_04);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10978750(int Index, int Count);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109c4c50_Array2
{
public:
    ~UnkType_109c4c50_Array2()
    {
        Unk_109c1960(0, unk_04);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_109c1960(int Index, int Count);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109c4c50_Base
{
public:
    ~UnkType_109c4c50_Base();

private:
    unsigned char unk_00[0x38];
};

class UnkType_109c4c50 : public UnkType_109c4c50_Base
{
public:
    ~UnkType_109c4c50();

private:
    UnkType_109c4c50_Table unk_38;
    UnkType_109c4c50_Array1 unk_4c;
    UnkType_109c4c50_Array2 unk_58;
};

// UnkType_109c4c50::~UnkType_109c4c50
UnkType_109c4c50::~UnkType_109c4c50()
{
}
