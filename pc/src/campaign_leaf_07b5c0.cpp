// campaign_leaf_07b5c0.cpp -- destructor at VA 0x1097b5c0 of a class whose vtable is at VA
// 0x110c10d8: calls the method at VA 0x10cd7a30; destroys the array member at 0xbc (removes its
// elements with the method at VA 0x10978980, frees its data through virtual slot 2 of the
// allocator the global at VA 0x111c88a0 points to and clears it); then runs the destructors of
// the three base classes whose vtables are at VA 0x110bf470, 0x110bf398 and 0x110bf2a8, each of
// which calls the method at VA 0x10cd7a30 again, before the base destructor at VA 0x10cdc460. The
// class, member and method names are invented; the offsets and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10978980_07b5c0
{
public:
    ~UnkType_10978980_07b5c0()
    {
        Unk_10978980(0, unk_04);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10978980(int Index, int Count);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_1097b5c0_Base
{
public:
    virtual ~UnkType_1097b5c0_Base();
    void Unk_10cd7a30();

private:
    unsigned char unk_04[0x2c];
};

class UnkType_110bf2a8 : public UnkType_1097b5c0_Base
{
public:
    virtual ~UnkType_110bf2a8()
    {
        Unk_10cd7a30();
    }
};

class UnkType_110bf398 : public UnkType_110bf2a8
{
public:
    virtual ~UnkType_110bf398()
    {
        Unk_10cd7a30();
    }
};

class UnkType_110bf470 : public UnkType_110bf398
{
public:
    virtual ~UnkType_110bf470()
    {
        Unk_10cd7a30();
    }

private:
    unsigned char unk_30[0xbc - 0x30];
};

class UnkType_1097b5c0 : public UnkType_110bf470
{
public:
    virtual ~UnkType_1097b5c0();

private:
    UnkType_10978980_07b5c0 unk_bc;
};

// UnkType_1097b5c0::~UnkType_1097b5c0
UnkType_1097b5c0::~UnkType_1097b5c0()
{
    Unk_10cd7a30();
}
