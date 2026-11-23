// campaign_leaf_2e6490.cpp -- destructor at VA 0x10be6490 of a class with a vtable (VA 0x110ec2e8):
// calls the method at VA 0x10cd7a30, then destroys the dynamic arrays at 0x2cc, 0x2c0 and 0x2b4
// (contents removed through the methods at VA 0x10929a90, VA 0x10929b20 and VA 0x10929b20, element
// size 4; data freed through virtual slot 2 of the allocator at VA 0x111c88a0; three words
// cleared), and runs the base class destructor at VA 0x1092ad20. The class, member and method names
// are invented; the offsets and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10be6490_Base
{
public:
    virtual ~UnkType_10be6490_Base();

    void Unk_10cd7a30();

private:
    unsigned char unk_04[0x2b4 - 0x04];
};

class UnkType_10be6490_Words
{
public:
    ~UnkType_10be6490_Words()
    {
        Unk_10929b20(0, unk_04, 4);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10929b20(int Index, int Count, int ElementSize);

    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10be6490_2cc
{
public:
    ~UnkType_10be6490_2cc()
    {
        Unk_10929a90(0, unk_04, 4);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_10929a90(int Index, int Count, int ElementSize);

    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10be6490 : public UnkType_10be6490_Base
{
public:
    virtual ~UnkType_10be6490();

private:
    UnkType_10be6490_Words unk_2b4;
    UnkType_10be6490_Words unk_2c0;
    UnkType_10be6490_2cc unk_2cc;
};

// UnkType_10be6490::~UnkType_10be6490
UnkType_10be6490::~UnkType_10be6490()
{
    Unk_10cd7a30();
}
