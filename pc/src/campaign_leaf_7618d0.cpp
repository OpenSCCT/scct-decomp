// campaign_leaf_7618d0.cpp -- one function at file offset 0x7618d0, preferred VA 0x110618d0. A
// constructor: after the base constructor at VA 0x110679f0 it installs the vtable at VA
// 0x11176228, sets the words at 0x68 and 0x70 to 1 and 0x38 to 0x10000, clears the 0x58-byte
// block at 0x74 through the stdcall function at VA 0x1103c650, clears the words at 0x4, 0x30,
// 0x34, 0x44, 0x48, 0x4c, 0x58, 0x5c, 0x60, 0x6c and 0x78, and sets the word at 0x74 to 1. The
// class and function names are invented; the offsets and the addresses are the binary's.

void __stdcall Unk_1103c650(void* Block, int Value, unsigned int Size);

class UnkType_110618d0_Base
{
public:
    UnkType_110618d0_Base();

    virtual void VirtualSlot0();

    int unk_4;
    unsigned char unk_8[0x30 - 0x8];
};

class UnkType_110618d0 : public UnkType_110618d0_Base
{
public:
    UnkType_110618d0();

    virtual void VirtualSlot0();

    int unk_30;
    int unk_34;
    int unk_38;
    unsigned char unk_3c[0x44 - 0x3c];
    int unk_44;
    int unk_48;
    int unk_4c;
    unsigned char unk_50[0x58 - 0x50];
    int unk_58;
    int unk_5c;
    int unk_60;
    unsigned char unk_64[0x68 - 0x64];
    int unk_68;
    int unk_6c;
    int unk_70;
    int unk_74;
    int unk_78;
};

// UnkType_110618d0::UnkType_110618d0
UnkType_110618d0::UnkType_110618d0()
{
    unk_58 = 0;
    unk_5c = 0;
    unk_60 = 0;
    unk_68 = 1;
    unk_6c = 0;
    unk_70 = 1;
    Unk_1103c650(&unk_74, 0, 0x58);
    unk_78 = 0;
    unk_30 = 0;
    unk_34 = 0;
    unk_4c = 0;
    unk_44 = 0;
    unk_48 = 0;
    unk_4 = 0;
    unk_38 = 0x10000;
    unk_74 = 1;
}
