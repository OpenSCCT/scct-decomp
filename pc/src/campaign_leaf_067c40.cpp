// campaign_leaf_067c40.cpp -- destructor at VA 0x10967c40 of a class whose vtable is at VA
// 0x110bed58: calls the method at VA 0x10cd7a30; destroys the array member at 0x54 (removes its
// elements with the method at VA 0x1090d050, frees its data through virtual slot 2 of the
// allocator the global at VA 0x111c88a0 points to and clears it) and the members at 0x48, 0x3c
// and 0x30 with the destructor at VA 0x1090ba70; then runs the base destructor at VA 0x10cdc460.
// The class, member and method names are invented; the offsets and the addresses are the
// binary's.

#include "campaign_global_111c88a0.h"

class UnkType_1090d050_067c40
{
public:
    ~UnkType_1090d050_067c40()
    {
        Unk_1090d050(0, unk_04);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_1090d050(int Index, int Count);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_1090ba70_067c40
{
public:
    ~UnkType_1090ba70_067c40();

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10cdc460
{
public:
    virtual ~UnkType_10cdc460();
    void Unk_10cd7a30();

private:
    unsigned char unk_04[0x2c];
};

class UnkType_10967c40 : public UnkType_10cdc460
{
public:
    virtual ~UnkType_10967c40();

private:
    UnkType_1090ba70_067c40 unk_30;
    UnkType_1090ba70_067c40 unk_3c;
    UnkType_1090ba70_067c40 unk_48;
    UnkType_1090d050_067c40 unk_54;
};

// UnkType_10967c40::~UnkType_10967c40
UnkType_10967c40::~UnkType_10967c40()
{
    Unk_10cd7a30();
}
