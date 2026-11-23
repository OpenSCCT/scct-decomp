// campaign_leaf_342a10.cpp -- one function at file offset 0x342a10, preferred VA 0x10c42a10. A
// destructor: it installs the vtable at 0x110ff550, calls the method at 0x10cd7a30, destroys the
// arrays at 0x458 (removing its 4-byte elements with the method at 0x10bd7270) and 0x44c (removing
// its 4-byte elements with the method at 0x10bd7270) and 0x440 (removing its 4-byte elements with
// the method at 0x10929a90), freeing their data through the allocator at 0x111c88a0, and ends in
// the base destructor at 0x10bee4f0. The class, method and member names are invented; the offsets
// and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10c42a10_Base
{
public:
    virtual ~UnkType_10c42a10_Base();

    unsigned char unk_4[0x43c];
};

class UnkType_10929a90
{
public:
    ~UnkType_10929a90()
    {
        Unk_10929a90(0, unk_4, 4);
        if ( unk_0 != 0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_8 = 0;
        unk_4 = 0;
    }

    void Unk_10929a90(int Index, int Count, int Size);

    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10bd7270
{
public:
    ~UnkType_10bd7270()
    {
        Unk_10bd7270(0, unk_4, 4);
        if ( unk_0 != 0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_8 = 0;
        unk_4 = 0;
    }

    void Unk_10bd7270(int Index, int Count, int Size);

    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10c42a10 : public UnkType_10c42a10_Base
{
public:
    virtual ~UnkType_10c42a10();
    void Unk_10cd7a30();

    UnkType_10929a90 unk_440;
    UnkType_10bd7270 unk_44c;
    UnkType_10bd7270 unk_458;
};

// UnkType_10c42a10::~UnkType_10c42a10
UnkType_10c42a10::~UnkType_10c42a10()
{
    Unk_10cd7a30();
}
