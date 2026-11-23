// campaign_leaf_76db20.cpp -- one function at file offset 0x76db20, preferred VA 0x1106db20. It
// returns -1 when the count at 0xc is set; otherwise it fills a 0x10-byte block through the
// source's method at VA 0x1105ef80 and returns -1 when the fourth virtual method rejects the
// block. It then stores the source at 0x20, increments the count, stores the block's word at 0x8,
// doubled, at 0x58 and returns 0. The class, method and member names are invented;
// the offsets and the addresses are the binary's.

struct UnkType_1106db20_Block
{
    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;
};

class UnkType_1106db20_Source
{
public:
    void Unk_1105ef80(UnkType_1106db20_Block* Block);
};

class UnkType_1106db20
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual int VirtualSlot3(UnkType_1106db20_Block* Block);

    int Unk_1106db20(UnkType_1106db20_Source* Source);

    int unk_4;
    int unk_8;
    int unk_c;
    unsigned char unk_10[0x20 - 0x10];
    UnkType_1106db20_Source* unk_20;
    unsigned char unk_24[0x58 - 0x24];
    int unk_58;
};

// UnkType_1106db20::Unk_1106db20
int UnkType_1106db20::Unk_1106db20(UnkType_1106db20_Source* Source)
{
    UnkType_1106db20_Block Block;

    if ( unk_c != 0 )
    {
        return -1;
    }
    Source->Unk_1105ef80(&Block);
    if ( VirtualSlot3(&Block) == 0 )
    {
        return -1;
    }
    unk_20 = Source;
    unk_c++;
    unk_58 = Block.unk_8 * 2;
    return 0;
}
