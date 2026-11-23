// campaign_leaf_775910.cpp -- one function at file offset 0x775910, preferred VA 0x11075910. It returns
// -1 when the count at 0xc is set; otherwise it has the source object's method at VA 0x1105ef80
// copy four words into a local and passes the local to the fourth virtual method, returning -1
// when that fails and otherwise storing the source at 0x5c and incrementing the count (returning
// 0). The class, method and member names are invented; the offsets and the callee's address are
// the binary's.

struct UnkType_11075910_Block
{
    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;
};

class UnkType_11075910_Source
{
public:
    void Unk_1105ef80(UnkType_11075910_Block* Block);
};

class UnkType_11075910
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual int VirtualSlot3(UnkType_11075910_Block* Block);

    int Unk_11075910(UnkType_11075910_Source* Source);

    int unk_4;
    int unk_8;
    int unk_c;
    unsigned char unk_10[0x5c - 0x10];
    UnkType_11075910_Source* unk_5c;
};

// UnkType_11075910::Unk_11075910
int UnkType_11075910::Unk_11075910(UnkType_11075910_Source* Source)
{
    UnkType_11075910_Block Block;

    if ( unk_c != 0 )
    {
        return -1;
    }
    Source->Unk_1105ef80(&Block);
    if ( VirtualSlot3(&Block) == 0 )
    {
        return -1;
    }
    unk_5c = Source;
    unk_c++;
    return 0;
}
