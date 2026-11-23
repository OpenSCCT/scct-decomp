// campaign_leaf_4fb7c0.cpp -- method at VA 0x10dfb7c0: allocates a 0x20-byte node (operator new at
// VA 0x10901480) holding its 24-byte argument, appends it to the list whose head is at 0x04 and
// tail at 0x08, and calls virtual slot 1. The class, method and member names are invented; the
// offsets, the slot and the address are the binary's.

class UnkType_10dfb7c0_Value
{
public:
    int unk_00[6];
};

class UnkType_10dfb7c0_Node
{
public:
    UnkType_10dfb7c0_Node* unk_00;
    UnkType_10dfb7c0_Node* unk_04;
    UnkType_10dfb7c0_Value unk_08;
};

class UnkType_10dfb7c0
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();

    void Unk_10dfb7c0(UnkType_10dfb7c0_Value Value);

    UnkType_10dfb7c0_Node* unk_04;
    UnkType_10dfb7c0_Node* unk_08;
};

// UnkType_10dfb7c0::Unk_10dfb7c0
void UnkType_10dfb7c0::Unk_10dfb7c0(UnkType_10dfb7c0_Value Value)
{
    UnkType_10dfb7c0_Node* Node = new UnkType_10dfb7c0_Node;
    Node->unk_00 = 0;
    Node->unk_04 = 0;
    Node->unk_08 = Value;
    if ( unk_08 == 0 )
    {
        unk_04 = Node;
        unk_08 = Node;
    }
    else
    {
        unk_08->unk_04 = Node;
        Node->unk_00 = unk_08;
        unk_08 = Node;
    }
    VirtualSlot1();
}
