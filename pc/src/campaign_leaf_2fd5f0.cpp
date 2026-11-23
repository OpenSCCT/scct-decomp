// campaign_leaf_2fd5f0.cpp -- destructor at VA 0x10bfd5f0 of a class with a vtable (VA 0x110f1e60):
// calls the method at VA 0x10cd7a30 and destroys the dynamic arrays at 0x428 and 0x41c (contents
// removed through the method at VA 0x10936690, element size 4; data freed through virtual slot 2 of
// the allocator at VA 0x111c88a0; three words cleared); then its parent class's inline destructor
// stores that class's vtable (VA 0x110f15c0), calls the same method and destroys the string at
// 0x410 (destructor at VA 0x1090ba70), and the root class destructor at VA 0x10bee4f0 runs. The
// class, member and method names are invented; the offsets and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10bfd5f0_Root
{
public:
    virtual ~UnkType_10bfd5f0_Root();

    void Unk_10cd7a30();

private:
    unsigned char unk_04[0x410 - 0x04];
};

class UnkType_10bfd5f0_String
{
public:
    ~UnkType_10bfd5f0_String();

private:
    unsigned short* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10bfd5f0_Parent : public UnkType_10bfd5f0_Root
{
public:
    virtual ~UnkType_10bfd5f0_Parent()
    {
        Unk_10cd7a30();
    }

private:
    UnkType_10bfd5f0_String unk_410;
};

class UnkType_10bfd5f0_Array
{
public:
    ~UnkType_10bfd5f0_Array()
    {
        Unk_10936690(0, unk_04, 4);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10936690(int Index, int Count, int ElementSize);

    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10bfd5f0 : public UnkType_10bfd5f0_Parent
{
public:
    virtual ~UnkType_10bfd5f0();

private:
    UnkType_10bfd5f0_Array unk_41c;
    UnkType_10bfd5f0_Array unk_428;
};

// UnkType_10bfd5f0::~UnkType_10bfd5f0
UnkType_10bfd5f0::~UnkType_10bfd5f0()
{
    Unk_10cd7a30();
}
