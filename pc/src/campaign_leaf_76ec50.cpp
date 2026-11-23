// campaign_leaf_76ec50.cpp -- one function at file offset 0x76ec50, preferred VA 0x1106ec50. It
// returns -1 when the count at 0xc is set; otherwise it fills a 0x10-byte block through the
// source's method at VA 0x1105ef80 and returns -1 when the fourth virtual method rejects the
// block. It then increments the count, stores the source at 0x20 and the block's word at 0x8 at
// 0x2c and, doubled, at 0x24, and returns 0. The class, method and member names are invented;
// the offsets and the addresses are the binary's.

struct UnkType_1106ec50_Block
{
    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;
};

class UnkType_1106ec50_Source
{
public:
    void Unk_1105ef80(UnkType_1106ec50_Block* Block);
};

class UnkType_1106ec50
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual int VirtualSlot3(UnkType_1106ec50_Block* Block);

    int Unk_1106ec50(UnkType_1106ec50_Source* Source);

    int unk_4;
    int unk_8;
    int unk_c;
    unsigned char unk_10[0x20 - 0x10];
    UnkType_1106ec50_Source* unk_20;
    int unk_24;
    int unk_28;
    int unk_2c;
};

// UnkType_1106ec50::Unk_1106ec50
int UnkType_1106ec50::Unk_1106ec50(UnkType_1106ec50_Source* Source)
{
    UnkType_1106ec50_Block Block;

    if ( unk_c != 0 )
    {
        return -1;
    }
    Source->Unk_1105ef80(&Block);
    if ( VirtualSlot3(&Block) == 0 )
    {
        return -1;
    }
    unk_c++;
    unk_20 = Source;
    unk_2c = Block.unk_8;
    unk_24 = Block.unk_8 * 2;
    return 0;
}
