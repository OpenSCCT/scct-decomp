// campaign_leaf_74be30.cpp -- one function at file offset 0x74be30, preferred VA 0x1104be30. When
// the word at 0x8 of its argument is non-zero it returns whether the word at 0x8 of the object this
// object's first word points to is the argument; otherwise it returns whether the unsigned word at
// 0x8 of this object is at most 1. The class, method and member names are invented; the offset and
// the bytes are the binary's.

struct UnkType_1104be30_Node
{
    int unk_0;
    int unk_4;
    UnkType_1104be30_Node* unk_8;
};

class UnkType_1104be30
{
public:
    int Unk_1104be30(UnkType_1104be30_Node* Node);

    UnkType_1104be30_Node* unk_0;
    int unk_4;
    unsigned int unk_8;
};

// UnkType_1104be30::Unk_1104be30
int UnkType_1104be30::Unk_1104be30(UnkType_1104be30_Node* Node)
{
    if ( Node->unk_8 != 0 )
    {
        return unk_0->unk_8 == Node;
    }
    return unk_8 <= 1;
}
