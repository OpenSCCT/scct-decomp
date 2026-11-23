// campaign_leaf_4b9980.cpp -- one function at file offset 0x4b9980, preferred VA 0x10db9980.
// It walks the circular list whose head node is at offset 0x14 and passes Value to the method at
// 0x10da4860 of the object each node holds. The class, structure, method, member and parameter
// names are invented; the offset and the bytes are the binary's.

class UnkType_10db9980_Item
{
public:
    void Unk_10da4860(int Value);
};

struct UnkType_10db9980_Node
{
    UnkType_10db9980_Node* unk_0;
    UnkType_10db9980_Node* unk_4;
    UnkType_10db9980_Item* unk_8;
};

class UnkType_10db9980
{
public:
    unsigned char unk_0[0x14];
    UnkType_10db9980_Node* unk_14;

    void Unk_10db9980(int Value);
};

// UnkType_10db9980::Unk_10db9980
void UnkType_10db9980::Unk_10db9980(int Value)
{
    UnkType_10db9980_Node* Node;

    for ( Node = unk_14->unk_0; Node != unk_14; Node = Node->unk_0 )
    {
        Node->unk_8->Unk_10da4860(Value);
    }
}
