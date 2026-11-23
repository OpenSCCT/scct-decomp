// campaign_leaf_0ad570.cpp -- virtual destructor at VA 0x109ad570 (vtable at VA 0x110ccc68): calls
// the method at VA 0x10cd7a30, destroys the five 0x2c-byte records at 0x88 in reverse order (each
// destroys its 16-bit array at 0x00: method at VA 0x10907710 with 0, its count and the element size
// 2, then frees its data through virtual slot 2 of the allocator global at VA 0x111c88a0), then
// runs the inline destructor of its base class (vtable at VA 0x110c0b98), which calls the same
// method, and ends in that class's base destructor at VA 0x10cdc460. The class, member and method
// names are invented; the offsets and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_109ad570_Base
{
public:
    virtual ~UnkType_109ad570_Base();
    void Unk_10cd7a30();
};

class UnkType_109ad570_Middle : public UnkType_109ad570_Base
{
public:
    virtual ~UnkType_109ad570_Middle()
    {
        Unk_10cd7a30();
    }
};

class UnkType_109ad570_Array
{
public:
    ~UnkType_109ad570_Array()
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

struct UnkType_109ad570_Record
{
    UnkType_109ad570_Array unk_00;
    unsigned char unk_0c[0x2c - 0x0c];
};

class UnkType_109ad570 : public UnkType_109ad570_Middle
{
public:
    virtual ~UnkType_109ad570();

private:
    unsigned char unk_04[0x88 - 0x04];
    UnkType_109ad570_Record unk_88[5];
};

// UnkType_109ad570::~UnkType_109ad570
UnkType_109ad570::~UnkType_109ad570()
{
    Unk_10cd7a30();
}
