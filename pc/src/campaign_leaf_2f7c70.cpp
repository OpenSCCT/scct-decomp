// campaign_leaf_2f7c70.cpp -- destructor at VA 0x10bf7c70 of a class with a vtable (VA 0x110effb0):
// calls the method at VA 0x10cd7a30 and destroys the dynamic array at 0x428 (contents removed
// through the method at VA 0x10bf7710 with 0x0c as the element size, data freed through virtual
// slot 2 of the allocator at VA 0x111c88a0, three words cleared); then runs its base class's
// destructor inline (vtable VA 0x110ef9a8: the method at VA 0x10cd7a30 again and the member at
// 0x3fc, destructor at VA 0x1090ba70) and finally the next base destructor at VA 0x10bee4f0. The
// class, member and method names are invented; the offsets and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10bf7c70_Root
{
public:
    virtual ~UnkType_10bf7c70_Root();

    void Unk_10cd7a30();

private:
    unsigned char unk_04[0x3fc - 0x04];
};

class UnkType_10bf7c70_3fc
{
public:
    ~UnkType_10bf7c70_3fc();

private:
    int unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10bf7c70_Base : public UnkType_10bf7c70_Root
{
public:
    virtual ~UnkType_10bf7c70_Base()
    {
        Unk_10cd7a30();
    }

private:
    UnkType_10bf7c70_3fc unk_3fc;
    unsigned char unk_408[0x428 - 0x408];
};

class UnkType_10bf7c70_428
{
public:
    ~UnkType_10bf7c70_428()
    {
        Unk_10bf7710(0, unk_04, 0x0c);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10bf7710(int Index, int Count, int ElementSize);

    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10bf7c70 : public UnkType_10bf7c70_Base
{
public:
    virtual ~UnkType_10bf7c70();

private:
    UnkType_10bf7c70_428 unk_428;
};

// UnkType_10bf7c70::~UnkType_10bf7c70
UnkType_10bf7c70::~UnkType_10bf7c70()
{
    Unk_10cd7a30();
}
