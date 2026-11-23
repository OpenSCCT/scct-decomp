// campaign_leaf_042cc0.cpp -- destructor at VA 0x10942cc0 of a class whose vtable is at VA
// 0x110bc720: calls the method at VA 0x10cd7a30, destroys the array member at 0x7b8 (removes its
// 12-byte elements with the method at VA 0x10929260, frees its data through virtual slot 2 of the
// allocator the global at VA 0x111c88a0 points to and clears it), then runs the base destructor at
// VA 0x1092c8a0. The class, member and method names are invented; the offsets, the size and the
// addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10929260_042cc0
{
public:
    ~UnkType_10929260_042cc0()
    {
        Unk_10929260(0, unk_04, 12);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10929260(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_1092c8a0
{
public:
    virtual ~UnkType_1092c8a0();
    void Unk_10cd7a30();

private:
    unsigned char unk_004[0x7b4];
};

class UnkType_10942cc0 : public UnkType_1092c8a0
{
public:
    virtual ~UnkType_10942cc0();

private:
    UnkType_10929260_042cc0 unk_7b8;
};

// UnkType_10942cc0::~UnkType_10942cc0
UnkType_10942cc0::~UnkType_10942cc0()
{
    Unk_10cd7a30();
}
