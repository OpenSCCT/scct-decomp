// campaign_leaf_74bed0.cpp -- one function at file offset 0x74bed0, preferred VA 0x1104bed0. It
// walks the singly linked list at 0x0 and, for every node whose record has the two argument values
// at 0xc and 0x8 and a zero word at 0x4, sets that word to 1 and the word at 0x10 to -1. The class,
// method and member names are invented; the offset and the bytes are the binary's.

struct UnkType_1104bed0_Record
{
    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;
    int unk_10;
};

struct UnkType_1104bed0_Node
{
    UnkType_1104bed0_Node* unk_0;
    int unk_4;
    UnkType_1104bed0_Record* unk_8;
};

class UnkType_1104bed0
{
public:
    void Unk_1104bed0(int First, int Second);

    UnkType_1104bed0_Node* unk_0;
};

// UnkType_1104bed0::Unk_1104bed0
void UnkType_1104bed0::Unk_1104bed0(int First, int Second)
{
    UnkType_1104bed0_Node* Node;
    UnkType_1104bed0_Node* Current;
    UnkType_1104bed0_Record* Record;

    Node = unk_0;
    while ( Node != 0 )
    {
        Current = Node;
        Node = Node->unk_0;
        Record = Current->unk_8;
        if ( Record->unk_c == First && Record->unk_8 == Second && Record->unk_4 == 0 )
        {
            Record->unk_4 = 1;
            Record->unk_10 = -1;
        }
    }
}
