// campaign_leaf_3c8300.cpp -- one function at file offset 0x3c8300, preferred VA 0x10cc8300. A
// destructor: it destroys the members at 0x88, 0x7c, 0x70 and 0x64 (destructor at 0x1090ba70),
// the array at 0x58 (removing its elements with the method at 0x1090d050 and freeing its data
// through the allocator at 0x111c88a0) and the member at 0x34. The class, method and member
// names are invented; the offsets and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_1090ba70
{
public:
    ~UnkType_1090ba70();

private:
    int unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10cc8300_1090d050
{
public:
    ~UnkType_10cc8300_1090d050()
    {
        Unk_1090d050(0, unk_4);
        if ( unk_0 != 0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_8 = 0;
        unk_4 = 0;
    }

    void Unk_1090d050(int Index, int Count);

    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10cc8300
{
public:
    ~UnkType_10cc8300();

    unsigned char unk_0[0x34];
    UnkType_1090ba70 unk_34;
    unsigned char unk_40[0x18];
    UnkType_10cc8300_1090d050 unk_58;
    UnkType_1090ba70 unk_64;
    UnkType_1090ba70 unk_70;
    UnkType_1090ba70 unk_7c;
    UnkType_1090ba70 unk_88;
    unsigned char unk_94[0x8];
};

// UnkType_10cc8300::~UnkType_10cc8300
UnkType_10cc8300::~UnkType_10cc8300()
{
}
