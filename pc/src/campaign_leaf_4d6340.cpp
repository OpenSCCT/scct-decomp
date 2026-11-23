// campaign_leaf_4d6340.cpp -- one function at file offset 0x4d6340, preferred VA 0x10dd6340.
// It walks the circular list whose head node is at offset 8 and passes Value to the method at
// 0x10d91080 of the object each node holds in place. The class, structure, method, member and
// parameter names are invented; the offset and the bytes are the binary's.

class UnkType_10dd6340_Item
{
public:
    void Unk_10d91080(int Value);
};

struct UnkType_10dd6340_Node
{
    UnkType_10dd6340_Node* unk_0;
    UnkType_10dd6340_Node* unk_4;
    UnkType_10dd6340_Item unk_8;
};

class UnkType_10dd6340
{
public:
    int unk_0;
    int unk_4;
    UnkType_10dd6340_Node* unk_8;

    void Unk_10dd6340(int Value);
};

// UnkType_10dd6340::Unk_10dd6340
void UnkType_10dd6340::Unk_10dd6340(int Value)
{
    UnkType_10dd6340_Node* Node;

    for ( Node = unk_8->unk_0; Node != unk_8; Node = Node->unk_0 )
    {
        Node->unk_8.Unk_10d91080(Value);
    }
}
