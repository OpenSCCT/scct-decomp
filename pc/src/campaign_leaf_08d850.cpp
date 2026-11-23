// campaign_leaf_08d850.cpp -- destructor at VA 0x1098d850 of a class whose vtable is at VA
// 0x110c1ff8: calls the method at VA 0x10cd7a30; destroys the array members at 0x5c (removes its
// elements with the method at VA 0x1098d5b0), 0x50, 0x44 and 0x38 (each removes its 4-byte
// elements with the method at VA 0x10929a90), freeing each one's data through virtual slot 2 of
// the allocator the global at VA 0x111c88a0 points to and clearing it; then runs the base
// destructor at VA 0x10cdc460. The class, member and method names are invented; the offsets, the
// size and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_1098d5b0_08d850
{
public:
    ~UnkType_1098d5b0_08d850()
    {
        Unk_1098d5b0(0, unk_04);
        if ( unk_00 )
        {
            GUnk_111c88a0->Free(unk_00);
        }
        unk_00 = 0;
        unk_04 = unk_08 = 0;
    }

    void Unk_1098d5b0(int Index, int Count);

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10929a90_08d850
{
public:
    ~UnkType_10929a90_08d850()
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

private:
    void* unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_1098d850_Base
{
public:
    virtual ~UnkType_1098d850_Base();
    void Unk_10cd7a30();

private:
    unsigned char unk_04[0x34];
};

class UnkType_1098d850 : public UnkType_1098d850_Base
{
public:
    virtual ~UnkType_1098d850();

private:
    UnkType_10929a90_08d850 unk_38;
    UnkType_10929a90_08d850 unk_44;
    UnkType_10929a90_08d850 unk_50;
    UnkType_1098d5b0_08d850 unk_5c;
};

// UnkType_1098d850::~UnkType_1098d850
UnkType_1098d850::~UnkType_1098d850()
{
    Unk_10cd7a30();
}
