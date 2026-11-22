// campaign_leaf_74bf10.cpp -- one function at file offset 0x74bf10, preferred VA 0x1104bf10. It
// walks the singly linked list at 0x0 and returns the word at 0x10 of the first record that has the
// two argument values at 0xc and 0x8 and a zero word at 0x4, or -1 when there is none. The class,
// method and member names are invented; the offset and the bytes are the binary's.

struct UnkType_1104bf10_Record
{
    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;
    int unk_10;
};

struct UnkType_1104bf10_Node
{
    UnkType_1104bf10_Node* unk_0;
    int unk_4;
    UnkType_1104bf10_Record* unk_8;
};

class UnkType_1104bf10
{
public:
    int Unk_1104bf10(int First, int Second);

    UnkType_1104bf10_Node* unk_0;
};

// UnkType_1104bf10::Unk_1104bf10
int UnkType_1104bf10::Unk_1104bf10(int First, int Second)
{
    UnkType_1104bf10_Node* Node;
    UnkType_1104bf10_Record* Record;
    UnkType_1104bf10_Node* Current;
    int Result;

    Result = -1;
    Node = unk_0;
    while ( Node != 0 )
    {
        Current = Node;
        Node = Node->unk_0;
        Record = Current->unk_8;
        if ( Record->unk_c == First && Record->unk_8 == Second && Record->unk_4 == 0 )
        {
            Result = Record->unk_10;
            break;
        }
    }
    return Result;
}
