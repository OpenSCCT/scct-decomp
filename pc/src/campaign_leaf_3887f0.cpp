// campaign_leaf_3887f0.cpp -- one function at file offset 0x3887f0, preferred VA 0x10c887f0. A
// destructor: it destroys the arrays at 0x330 (removing its 1-byte elements with the method at
// 0x10966210) and 0x1ac (removing its 0x178-byte elements with the method at 0x10c859f0),
// freeing their data through the allocator at 0x111c88a0. The class, method and member names are
// invented; the offsets and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10c859f0
{
public:
    ~UnkType_10c859f0()
    {
        Unk_10c859f0(0, unk_4, 0x178);
        if ( unk_0 != 0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_8 = 0;
        unk_4 = 0;
    }

    void Unk_10c859f0(int Index, int Count, int Size);

    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10966210
{
public:
    ~UnkType_10966210()
    {
        Unk_10966210(0, unk_4, 1);
        if ( unk_0 != 0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_8 = 0;
        unk_4 = 0;
    }

    void Unk_10966210(int Index, int Count, int Size);

    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10c887f0
{
public:
    ~UnkType_10c887f0();

    unsigned char unk_0[0x1ac];
    UnkType_10c859f0 unk_1ac;
    unsigned char unk_1b8[0x178];
    UnkType_10966210 unk_330;
};

// UnkType_10c887f0::~UnkType_10c887f0
UnkType_10c887f0::~UnkType_10c887f0()
{
}
