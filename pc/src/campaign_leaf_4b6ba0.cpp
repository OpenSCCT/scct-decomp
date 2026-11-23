// campaign_leaf_4b6ba0.cpp -- one function at file offset 0x4b6ba0, preferred VA 0x10db6ba0.
// It walks the circular list whose head node is at offset 8 and makes the virtual call in slot 3
// on the object each node holds. The class, structure and member names are invented; the offset
// and the bytes are the binary's.

class UnkType_10db6ba0_Item
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
};

struct UnkType_10db6ba0_Node
{
    UnkType_10db6ba0_Node* unk_0;
    UnkType_10db6ba0_Node* unk_4;
    UnkType_10db6ba0_Item* unk_8;
};

class UnkType_10db6ba0
{
public:
    int unk_0;
    int unk_4;
    UnkType_10db6ba0_Node* unk_8;

    void Unk_10db6ba0();
};

// UnkType_10db6ba0::Unk_10db6ba0
void UnkType_10db6ba0::Unk_10db6ba0()
{
    UnkType_10db6ba0_Node* Node;

    for ( Node = unk_8->unk_0; Node != unk_8; Node = Node->unk_0 )
    {
        Node->unk_8->VirtualSlot3();
    }
}
