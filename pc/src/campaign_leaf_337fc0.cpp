// campaign_leaf_337fc0.cpp -- one function at file offset 0x337fc0, preferred VA 0x10c37fc0. It
// allocates a 0x10-byte node (function at 0x10901480) holding Value, links it at the tail of the
// doubly linked list whose head is at 0x4 and tail at 0x8, and calls its own virtual slot 1. The
// class, method, structure, member and parameter names are invented; the offsets, the slot and
// the bytes are the binary's.

struct UnkType_10c37fc0_Value
{
    int unk_0;
    int unk_4;
};

struct UnkType_10c37fc0_Node
{
    UnkType_10c37fc0_Node* unk_0;
    UnkType_10c37fc0_Node* unk_4;
    UnkType_10c37fc0_Value unk_8;
};

void* Unk_10901480(unsigned int Size);

class UnkType_10c37fc0
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    void Unk_10c37fc0(UnkType_10c37fc0_Value Value);

    UnkType_10c37fc0_Node* unk_4;
    UnkType_10c37fc0_Node* unk_8;
};

// UnkType_10c37fc0::Unk_10c37fc0
void UnkType_10c37fc0::Unk_10c37fc0(UnkType_10c37fc0_Value Value)
{
    UnkType_10c37fc0_Node* Node = (UnkType_10c37fc0_Node*)Unk_10901480(0x10);

    Node->unk_0 = 0;
    Node->unk_4 = 0;
    Node->unk_8 = Value;
    if ( unk_8 == 0 )
    {
        unk_4 = Node;
        unk_8 = Node;
    }
    else
    {
        unk_8->unk_4 = Node;
        Node->unk_0 = unk_8;
        unk_8 = Node;
    }
    VirtualSlot1();
}
