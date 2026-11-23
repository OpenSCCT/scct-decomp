// campaign_leaf_3e8560.cpp -- one function at file offset 0x3e8560, preferred VA 0x10ce8560. A
// destructor: it installs the vtable at 0x11133648, calls the method at 0x10cd7a30, destroys the
// array at 0x38 (removing its elements with the method at 0x1090d050 and freeing its data through
// the allocator at 0x111c88a0), destroys the member at 0x2c (destructor at 0x1090ba70) and ends
// in the base destructor at 0x10cdc460. The class, method and member names are invented; the
// offsets and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10ce8560_Base
{
public:
    virtual ~UnkType_10ce8560_Base();

    unsigned char unk_4[0x28];
};

class UnkType_1090ba70
{
public:
    ~UnkType_1090ba70();

private:
    int unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10ce8560_1090d050
{
public:
    ~UnkType_10ce8560_1090d050()
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

class UnkType_10ce8560 : public UnkType_10ce8560_Base
{
public:
    virtual ~UnkType_10ce8560();
    void Unk_10cd7a30();

    UnkType_1090ba70 unk_2c;
    UnkType_10ce8560_1090d050 unk_38;
};

// UnkType_10ce8560::~UnkType_10ce8560
UnkType_10ce8560::~UnkType_10ce8560()
{
    Unk_10cd7a30();
}
