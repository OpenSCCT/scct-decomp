// campaign_leaf_76f570.cpp -- one function at file offset 0x76f570, preferred VA 0x1106f570. It
// calls its own sixteenth virtual method, copies the 0x18-byte block of its first argument to
// 0x28, sets the word at 0x10 to 2, clears the words at 0x24 and 0x40, stores at 0x44 the result
// of the stdcall function at VA 0x1104b270 on 0x8000 and the block's word at 0xc, and returns 1.
// The class, method and member names are invented; the offsets and the callee's address are the
// binary's.

int __stdcall Unk_1104b270(int Value, int Scale);

struct UnkType_1106f570_Block
{
    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;
    int unk_10;
    int unk_14;
};

class UnkType_1106f570
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void VirtualSlot9();
    virtual void VirtualSlot10();
    virtual void VirtualSlot11();
    virtual void VirtualSlot12();
    virtual void VirtualSlot13();
    virtual void VirtualSlot14();
    virtual void VirtualSlot15();

    int Unk_1106f570(UnkType_1106f570_Block* Block, int Unused);

    unsigned char unk_4[0x10 - 0x4];
    int unk_10;
    unsigned char unk_14[0x24 - 0x14];
    int unk_24;
    UnkType_1106f570_Block unk_28;
    int unk_40;
    int unk_44;
};

// UnkType_1106f570::Unk_1106f570
int UnkType_1106f570::Unk_1106f570(UnkType_1106f570_Block* Block, int Unused)
{
    VirtualSlot15();
    unk_28 = *Block;
    unk_10 = 2;
    unk_24 = 0;
    unk_40 = 0;
    unk_44 = Unk_1104b270(0x8000, Block->unk_c);
    return 1;
}
