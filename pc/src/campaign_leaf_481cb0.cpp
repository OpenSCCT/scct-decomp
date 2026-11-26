// campaign_leaf_481cb0.cpp -- destructor at VA 0x10d81cb0. It calls the method at 0x10d8ed80 of
// its reference at 0xb54 when that holds an object, then destroys its list at 0xb60 (whose buffer
// goes back to the allocator with tag 7) and the reference (0x10d8edb0). The inline destructor of
// its middle base follows, destroying the parts at 0xb50, 0xb4c (0x10d9d570), 0xa44 (0x10db4810)
// and 0x44 (0x10db4c90), before the base destructor at 0x10da2740. The class and member names
// are invented.

#include "campaign_leaf_481cb0_parts.h"

void* Unk_10d8b460();
void Unk_10d8b550(void* Heap, void* Block, int Tag);

// guess: the inline that returns a block to the allocator at 0x10d8b460 with tag 7
inline void FreeBlock(void* Block)
{
    Unk_10d8b550(Unk_10d8b460(), Block, 7);
}

class UnkType_10d81cb0_Base
{
public:
    virtual ~UnkType_10d81cb0_Base();

private:
    unsigned char unk_4[0x40];
};

class UnkType_10d81cb0_Word
{
public:
    ~UnkType_10d81cb0_Word();

private:
    int unk_0;
};

class UnkType_10d81cb0_Middle : public UnkType_10d81cb0_Base
{
public:
    virtual ~UnkType_10d81cb0_Middle()
    {
    }

private:
    UnkType_10d81cb0_Part44 unk_44;
    UnkType_10d81cb0_PartA44 unk_a44;
    UnkType_10d81cb0_Word unk_b4c;
    UnkType_10d81cb0_Word unk_b50;
};

class UnkType_10d81cb0_Ref
{
public:
    ~UnkType_10d81cb0_Ref();
    void Unk_10d8ed80();

    void* unk_0;

private:
    int unk_4;
    int unk_8;
};

class UnkType_10d81cb0_Items
{
public:
    ~UnkType_10d81cb0_Items()
    {
        Unk_10d81300();
        FreeBlock(unk_4);
        unk_4 = 0;
    }

    void Unk_10d81300();

private:
    int unk_0;
    void* unk_4;
    int unk_8;
    int unk_c;
};

class UnkType_10d81cb0 : public UnkType_10d81cb0_Middle
{
public:
    ~UnkType_10d81cb0();

private:
    UnkType_10d81cb0_Ref unk_b54;
    UnkType_10d81cb0_Items unk_b60;
};

// UnkType_10d81cb0::~UnkType_10d81cb0
UnkType_10d81cb0::~UnkType_10d81cb0()
{
    if ( unk_b54.unk_0 != 0 )
    {
        unk_b54.Unk_10d8ed80();
    }
}
