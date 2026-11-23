// campaign_leaf_1d8790.cpp -- destructor at VA 0x10ad8790. It calls the class's method at VA
// 0x10ad8360, then destroys the strings at 0x4c, 0x40 and 0x34 (destructor at VA 0x1090ba70) and
// the array of 4-byte elements at 0x24: its method at VA 0x10ad6600 removes all elements, its data
// is freed through slot 2 of the allocator at VA 0x111c88a0, and its three words are cleared. The
// class, method and member names are invented.

#include "campaign_global_111c88a0.h"

class UnkType_10ad8790_String
{
public:
    ~UnkType_10ad8790_String();

private:
    unsigned short* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10ad6600
{
public:
    // UnkType_10ad6600::~UnkType_10ad6600
    ~UnkType_10ad6600()
    {
        Unk_10ad6600(0, unk_4, 4);
        if ( unk_0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_4 = unk_8 = 0;
    }

    void Unk_10ad6600(int Index, int Count, int ElementSize);

private:
    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10ad8790
{
public:
    ~UnkType_10ad8790();

    void Unk_10ad8360();

private:
    char unk_00[0x24];
    UnkType_10ad6600 unk_24;
    int unk_30;
    UnkType_10ad8790_String unk_34;
    UnkType_10ad8790_String unk_40;
    UnkType_10ad8790_String unk_4c;
};

// UnkType_10ad8790::~UnkType_10ad8790
UnkType_10ad8790::~UnkType_10ad8790()
{
    Unk_10ad8360();
}
