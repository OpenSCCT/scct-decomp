// campaign_leaf_0adfc0.cpp -- virtual destructor at VA 0x109adfc0 (vtable at VA 0x110ccdc8): calls
// the method at VA 0x109abbc0, destroys the twelve 0x38-byte records at 0xb8 in reverse order (each
// destroys its 16-bit array at 0x00: method at VA 0x10907710 with 0, its count and the element size
// 2, then frees its data through virtual slot 2 of the allocator global at VA 0x111c88a0) and ends
// in the base class destructor at VA 0x10cdc460. The class, member and method names are invented;
// the offsets and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_109adfc0_Base
{
public:
    virtual ~UnkType_109adfc0_Base();
};

class UnkType_109adfc0_Array
{
public:
    ~UnkType_109adfc0_Array()
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

struct UnkType_109adfc0_Record
{
    UnkType_109adfc0_Array unk_00;
    unsigned char unk_0c[0x38 - 0x0c];
};

class UnkType_109adfc0 : public UnkType_109adfc0_Base
{
public:
    virtual ~UnkType_109adfc0();
    void Unk_109abbc0();

private:
    unsigned char unk_04[0xb8 - 0x04];
    UnkType_109adfc0_Record unk_b8[12];
};

// UnkType_109adfc0::~UnkType_109adfc0
UnkType_109adfc0::~UnkType_109adfc0()
{
    Unk_109abbc0();
}
