// campaign_leaf_0f3640.cpp -- destructor at VA 0x109f3640: destroys the dynamic arrays at 0x70
// (method at VA 0x10907710, element size 2) and 0x44 (method at VA 0x109d9640, element size 0x24),
// then the record at 0x18: frees its pointer at 0x0c, clears it and the count at 0x10, and destroys
// its dynamic array at 0x00 (method at VA 0x109d9db0, element size 8). Each destroyed array is
// passed 0 and its count and then has its data freed, all through virtual slot 2 of the allocator
// global at VA 0x111c88a0. The class, member and method names are invented; the offsets and the
// addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_109f3640_Pairs
{
public:
    ~UnkType_109f3640_Pairs()
    {
        Unk_109d9db0(0, unk_04, 8);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_109d9db0(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109f3640_Table
{
public:
    ~UnkType_109f3640_Table()
    {
        if ( unk_0c )
        {
            GUnk_111c88a0->Free(unk_0c);
        }
        unk_0c = 0;
        unk_10 = 0;
    }

private:
    UnkType_109f3640_Pairs unk_00;
    void* unk_0c;
    int unk_10;
};

class UnkType_109f3640_Records
{
public:
    ~UnkType_109f3640_Records()
    {
        Unk_109d9640(0, unk_04, 0x24);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_109d9640(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109f3640_Text
{
public:
    ~UnkType_109f3640_Text()
    {
        Unk_10907710(0, unk_04, 2);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10907710(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109f3640
{
public:
    ~UnkType_109f3640();

private:
    unsigned char unk_00[0x18];
    UnkType_109f3640_Table unk_18;
    unsigned char unk_2c[0x44 - 0x2c];
    UnkType_109f3640_Records unk_44;
    unsigned char unk_50[0x70 - 0x50];
    UnkType_109f3640_Text unk_70;
};

// UnkType_109f3640::~UnkType_109f3640
UnkType_109f3640::~UnkType_109f3640()
{
}
