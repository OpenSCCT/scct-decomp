// campaign_leaf_22c260.cpp -- the destructor at VA 0x10b2c260: it installs the class's virtual
// tables at 0x00 and 0x08 and calls the member at VA 0x10b2bc90; then the array at 0x74 is
// destroyed (its member at VA 0x1090d050 removes all elements, its block is freed through virtual
// slot 2 of the allocator the global at VA 0x111c88a0 points to and it is cleared), the string at
// 0x1c is destroyed with the destructor at VA 0x1090ba70, and the base destructor at VA 0x10b2a650
// runs. The class, method and member names are invented; the offsets, addresses and slot are the
// binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10b2c260_Face0
{
public:
    virtual void Malloc();

private:
    int unk_04;
};

class UnkType_10b2c260_Face8
{
public:
    virtual void Malloc();
};

class UnkType_10b2c260_Base : public UnkType_10b2c260_Face0, public UnkType_10b2c260_Face8
{
public:
    ~UnkType_10b2c260_Base();

    bool Unk_10b2bc90();

private:
    unsigned char unk_0c[0x1c - 0x0c];
};

class UnkType_10b2c260_String
{
public:
    ~UnkType_10b2c260_String();

private:
    int unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10b2c260_Array
{
public:
    void Unk_1090d050(int Index, int Count);

    // guess: removes the elements and frees the block (an inline destructor)
    ~UnkType_10b2c260_Array()
    {
        Unk_1090d050(0, unk_04);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_08 = 0;
        unk_04 = 0;
    }

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10b2c260 : public UnkType_10b2c260_Base
{
public:
    ~UnkType_10b2c260();

private:
    UnkType_10b2c260_String unk_1c;
    unsigned char unk_28[0x74 - 0x28];
    UnkType_10b2c260_Array unk_74;
};

// UnkType_10b2c260::~UnkType_10b2c260
UnkType_10b2c260::~UnkType_10b2c260()
{
    Unk_10b2bc90();
}
