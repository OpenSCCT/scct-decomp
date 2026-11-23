// campaign_leaf_321010.cpp -- one function at file offset 0x321010, preferred VA 0x10c21010. A
// destructor: it installs the vtable at 0x110f8ff8, calls the method at 0x10cd7a30, destroys the
// arrays at 0x6c (removing its 4-byte elements with the method at 0x10936690) and 0x30 (removing
// its 4-byte elements with the method at 0x10929a90), freeing their data through the allocator
// at 0x111c88a0, and ends in the base destructor at 0x10cdc460. The class, method and member
// names are invented; the offsets and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10c21010_Base
{
public:
    virtual ~UnkType_10c21010_Base();

    unsigned char unk_4[0x2c];
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

class UnkType_10936690
{
public:
    ~UnkType_10936690()
    {
        Unk_10936690(0, unk_4, 4);
        if ( unk_0 != 0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_8 = 0;
        unk_4 = 0;
    }

    void Unk_10936690(int Index, int Count, int Size);

    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10c21010 : public UnkType_10c21010_Base
{
public:
    virtual ~UnkType_10c21010();
    void Unk_10cd7a30();

    UnkType_10929a90 unk_30;
    unsigned char unk_3c[0x30];
    UnkType_10936690 unk_6c;
};

// UnkType_10c21010::~UnkType_10c21010
UnkType_10c21010::~UnkType_10c21010()
{
    Unk_10cd7a30();
}
