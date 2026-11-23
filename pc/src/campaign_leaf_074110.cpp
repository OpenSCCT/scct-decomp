// campaign_leaf_074110.cpp -- destructor at VA 0x10974110 of a class whose vtable is at VA
// 0x110c0c30: calls the method at VA 0x10cd7a30; destroys the array members at 0x60 (removes its
// 16-byte elements with the method at VA 0x10973ad0) and 0x54 (removes its elements with the
// method at VA 0x10973e90), freeing each one's data through virtual slot 2 of the allocator the
// global at VA 0x111c88a0 points to and clearing it; then runs the destructor of the base class
// whose vtable is at VA 0x110c0b98, which calls the method at VA 0x10cd7a30 again before the base
// destructor at VA 0x10cdc460. The class, member and method names are invented; the offsets, the
// size and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10973ad0_074110
{
public:
    ~UnkType_10973ad0_074110()
    {
        Unk_10973ad0(0, unk_04, 16);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10973ad0(int Index, int Count, int ElementSize);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10973e90_074110
{
public:
    ~UnkType_10973e90_074110()
    {
        Unk_10973e90(0, unk_04);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10973e90(int Index, int Count);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10974110_Base
{
public:
    virtual ~UnkType_10974110_Base();
    void Unk_10cd7a30();

private:
    unsigned char unk_04[0x2c];
};

class UnkType_110c0b98 : public UnkType_10974110_Base
{
public:
    virtual ~UnkType_110c0b98()
    {
        Unk_10cd7a30();
    }

private:
    unsigned char unk_30[0x24];
};

class UnkType_10974110 : public UnkType_110c0b98
{
public:
    virtual ~UnkType_10974110();

private:
    UnkType_10973e90_074110 unk_54;
    UnkType_10973ad0_074110 unk_60;
};

// UnkType_10974110::~UnkType_10974110
UnkType_10974110::~UnkType_10974110()
{
    Unk_10cd7a30();
}
