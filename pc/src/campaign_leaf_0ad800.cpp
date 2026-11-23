// campaign_leaf_0ad800.cpp -- virtual destructor at VA 0x109ad800 (vtable at VA 0x110ccce8): calls
// the method at VA 0x10cd7a30, then destroys the five 0x2c-byte records at 0x158 and the four at
// 0x88, last first, each by destroying the dynamic array of wide characters it starts with (method
// at VA 0x10907710 with 0, its count and the element size 2, then frees its data through virtual
// slot 2 of the allocator global at VA 0x111c88a0); then the inline destructor of its base class
// (vtable at VA 0x110c0b98) calls the same method, and it ends in the outermost base destructor at
// VA 0x10cdc460. The class, member and method names are invented; the offsets and the addresses
// are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_109ad800_Text
{
public:
    ~UnkType_109ad800_Text()
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

struct UnkType_109ad800_Record
{
    UnkType_109ad800_Text unk_00;
    unsigned char unk_0c[0x2c - 0x0c];
};

class UnkType_109ad800_Base
{
public:
    virtual ~UnkType_109ad800_Base();
    void Unk_10cd7a30();

private:
    unsigned char unk_04[0x88 - 0x04];
};

class UnkType_109ad800_Level1 : public UnkType_109ad800_Base
{
public:
    virtual ~UnkType_109ad800_Level1()
    {
        Unk_10cd7a30();
    }
};

class UnkType_109ad800 : public UnkType_109ad800_Level1
{
public:
    virtual ~UnkType_109ad800();

private:
    UnkType_109ad800_Record unk_88[4];
    unsigned char unk_138[0x158 - 0x138];
    UnkType_109ad800_Record unk_158[5];
};

// UnkType_109ad800::~UnkType_109ad800
UnkType_109ad800::~UnkType_109ad800()
{
    Unk_10cd7a30();
}
