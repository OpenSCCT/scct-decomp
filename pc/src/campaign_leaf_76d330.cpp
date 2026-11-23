// campaign_leaf_76d330.cpp -- one function at file offset 0x76d330, preferred VA 0x1106d330. It
// walks the list that starts at the pointer at 0x20, following each node's pointer at 0x0, and
// calls the method at VA 0x11072bb0 on the object at 0x14 of the item at 0x8 of every node. The
// type, method and member names are invented; the offsets and the callee's address are the
// binary's.

class UnkType_1106d330_Target
{
public:
    void Unk_11072bb0();
};

struct UnkType_1106d330_Item
{
    unsigned char unk_0[0x14];
    UnkType_1106d330_Target* unk_14;
};

struct UnkType_1106d330_Node
{
    UnkType_1106d330_Node* unk_0;
    int unk_4;
    UnkType_1106d330_Item* unk_8;
};

class UnkType_1106d330
{
public:
    void Unk_1106d330();

    unsigned char unk_0[0x20];
    UnkType_1106d330_Node* unk_20;
};

// UnkType_1106d330::Unk_1106d330
void UnkType_1106d330::Unk_1106d330()
{
    UnkType_1106d330_Node* Node;
    UnkType_1106d330_Node* Current;

    Node = unk_20;
    while ( Node != 0 )
    {
        Current = Node;
        Node = Node->unk_0;
        Current->unk_8->unk_14->Unk_11072bb0();
    }
}
