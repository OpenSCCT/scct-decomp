// campaign_leaf_4fb880.cpp -- method at VA 0x10dfb880: unlinks the first node of the list whose head
// is at 0x04 and tail at 0x08 (the list the method at VA 0x10dfb7c0 appends to), frees it
// (operator delete at VA 0x109014a0), calls virtual slot 2 and returns the node's 24-byte value.
// The class, method and member names are invented; the offsets, the slot and the address are the
// binary's.

class UnkType_10dfb880_Value
{
public:
    int unk_00[6];
};

class UnkType_10dfb880_Node
{
public:
    UnkType_10dfb880_Node* unk_00;
    UnkType_10dfb880_Node* unk_04;
    UnkType_10dfb880_Value unk_08;
};

class UnkType_10dfb880
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();

    UnkType_10dfb880_Value Unk_10dfb880();

    UnkType_10dfb880_Node* unk_04;
    UnkType_10dfb880_Node* unk_08;
};

// UnkType_10dfb880::Unk_10dfb880
UnkType_10dfb880_Value UnkType_10dfb880::Unk_10dfb880()
{
    UnkType_10dfb880_Node* Node = unk_04;
    unk_04 = Node->unk_04;
    if ( unk_04 != 0 )
    {
        unk_04->unk_00 = 0;
    }
    else
    {
        unk_08 = 0;
    }
    UnkType_10dfb880_Value Value = Node->unk_08;
    delete Node;
    VirtualSlot2();
    return Value;
}
