// campaign_leaf_774950.cpp -- one function at file offset 0x774950, preferred VA 0x11074950. It returns
// -1 when the count at 0xc is set; otherwise it has the source object's method at VA 0x1105ef80
// copy four words into a local and passes the local to the fourth virtual method, returning -1
// when that fails and otherwise storing the source at 0x24 and incrementing the count (returning
// 0). The class, method and member names are invented; the offsets and the callee's address are
// the binary's.

struct UnkType_11074950_Block
{
    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;
};

class UnkType_11074950_Source
{
public:
    void Unk_1105ef80(UnkType_11074950_Block* Block);
};

class UnkType_11074950
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual int VirtualSlot3(UnkType_11074950_Block* Block);

    int Unk_11074950(UnkType_11074950_Source* Source);

    int unk_4;
    int unk_8;
    int unk_c;
    unsigned char unk_10[0x24 - 0x10];
    UnkType_11074950_Source* unk_24;
};

// UnkType_11074950::Unk_11074950
int UnkType_11074950::Unk_11074950(UnkType_11074950_Source* Source)
{
    UnkType_11074950_Block Block;

    if ( unk_c != 0 )
    {
        return -1;
    }
    Source->Unk_1105ef80(&Block);
    if ( VirtualSlot3(&Block) == 0 )
    {
        return -1;
    }
    unk_24 = Source;
    unk_c++;
    return 0;
}
