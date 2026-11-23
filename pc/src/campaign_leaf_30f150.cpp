// campaign_leaf_30f150.cpp -- one function at file offset 0x30f150, preferred VA 0x10c0f150. A
// destructor: it installs the vtable at 0x110f6ee8, calls the method at 0x10cd7a30, destroys the
// arrays at 0x2c0 (removing its 4-byte elements with the method at 0x10929df0) and 0x2b4 (removing
// its 0x10-byte elements with the method at 0x10c0efb0), freeing their data through the allocator
// at 0x111c88a0, and ends in the base destructor at 0x1092ad20. The class, method and member names
// are invented; the offsets and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10c0f150_Base
{
public:
    virtual ~UnkType_10c0f150_Base();

    unsigned char unk_4[0x2b0];
};

class UnkType_10c0efb0
{
public:
    ~UnkType_10c0efb0()
    {
        Unk_10c0efb0(0, unk_4, 0x10);
        if ( unk_0 != 0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_8 = 0;
        unk_4 = 0;
    }

    void Unk_10c0efb0(int Index, int Count, int Size);

    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10929df0
{
public:
    ~UnkType_10929df0()
    {
        Unk_10929df0(0, unk_4, 4);
        if ( unk_0 != 0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_8 = 0;
        unk_4 = 0;
    }

    void Unk_10929df0(int Index, int Count, int Size);

    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10c0f150 : public UnkType_10c0f150_Base
{
public:
    virtual ~UnkType_10c0f150();
    void Unk_10cd7a30();

    UnkType_10c0efb0 unk_2b4;
    UnkType_10929df0 unk_2c0;
};

// UnkType_10c0f150::~UnkType_10c0f150
UnkType_10c0f150::~UnkType_10c0f150()
{
    Unk_10cd7a30();
}
