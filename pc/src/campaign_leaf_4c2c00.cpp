// campaign_leaf_4c2c00.cpp -- one function at file offset 0x4c2c00, preferred VA 0x10dc2c00.
// It walks the circular list whose head node is at offset 0x1c, makes the virtual call in slot 16
// on the object each node holds and returns the results combined with bitwise or. The class,
// structure and member names are invented; the offset and the bytes are the binary's.

class UnkType_10dc2c00_Item
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
    virtual int VirtualSlot16();
};

struct UnkType_10dc2c00_Node
{
    UnkType_10dc2c00_Node* unk_0;
    UnkType_10dc2c00_Node* unk_4;
    UnkType_10dc2c00_Item* unk_8;
};

class UnkType_10dc2c00
{
public:
    unsigned char unk_0[0x1c];
    UnkType_10dc2c00_Node* unk_1c;

    int Unk_10dc2c00();
};

// UnkType_10dc2c00::Unk_10dc2c00
int UnkType_10dc2c00::Unk_10dc2c00()
{
    int Result = 0;
    UnkType_10dc2c00_Node* Node;

    for ( Node = unk_1c->unk_0; Node != unk_1c; Node = Node->unk_0 )
    {
        Result |= Node->unk_8->VirtualSlot16();
    }
    return Result;
}
