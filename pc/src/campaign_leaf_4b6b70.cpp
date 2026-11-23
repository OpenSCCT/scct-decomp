// campaign_leaf_4b6b70.cpp -- one function at file offset 0x4b6b70, preferred VA 0x10db6b70.
// It walks the circular list whose head node is at offset 8 and makes the virtual call in slot 2
// on the object each node holds. The class, structure and member names are invented; the offset
// and the bytes are the binary's.

class UnkType_10db6b70_Item
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
};

struct UnkType_10db6b70_Node
{
    UnkType_10db6b70_Node* unk_0;
    UnkType_10db6b70_Node* unk_4;
    UnkType_10db6b70_Item* unk_8;
};

class UnkType_10db6b70
{
public:
    int unk_0;
    int unk_4;
    UnkType_10db6b70_Node* unk_8;

    void Unk_10db6b70();
};

// UnkType_10db6b70::Unk_10db6b70
void UnkType_10db6b70::Unk_10db6b70()
{
    UnkType_10db6b70_Node* Node;

    for ( Node = unk_8->unk_0; Node != unk_8; Node = Node->unk_0 )
    {
        Node->unk_8->VirtualSlot2();
    }
}
