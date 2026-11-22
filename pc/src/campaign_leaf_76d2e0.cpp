// campaign_leaf_76d2e0.cpp -- one function at file offset 0x76d2e0, preferred VA 0x1106d2e0. It
// walks the singly linked list at 0x20 for a record whose word at 0x24 is its argument and returns
// it; failing that it takes the first record whose word at 0x20 is zero, stores the argument at
// its 0x24 and returns it; otherwise it returns null. The class, method and member names are
// invented; the offset and the bytes are the binary's.

struct UnkType_1106d2e0_Record
{
    unsigned char unk_0[0x20];
    int unk_20;
    int unk_24;
};

struct UnkType_1106d2e0_Node
{
    UnkType_1106d2e0_Node* unk_0;
    int unk_4;
    UnkType_1106d2e0_Record* unk_8;
};

class UnkType_1106d2e0
{
public:
    UnkType_1106d2e0_Record* Unk_1106d2e0(int Value);

    unsigned char unk_0[0x20];
    UnkType_1106d2e0_Node* unk_20;
};

// UnkType_1106d2e0::Unk_1106d2e0
UnkType_1106d2e0_Record* UnkType_1106d2e0::Unk_1106d2e0(int Value)
{
    UnkType_1106d2e0_Node* Node;
    UnkType_1106d2e0_Node* Current;
    UnkType_1106d2e0_Record* Record;

    Node = unk_20;
    while ( Node != 0 )
    {
        Current = Node;
        Node = Node->unk_0;
        Record = Current->unk_8;
        if ( Record->unk_24 == Value )
        {
            return Record;
        }
    }
    Node = unk_20;
    while ( Node != 0 )
    {
        Current = Node;
        Node = Node->unk_0;
        Record = Current->unk_8;
        if ( Record->unk_20 == 0 )
        {
            Record->unk_24 = Value;
            return Record;
        }
    }
    return 0;
}
