// campaign_leaf_766ec0.cpp -- one function at file offset 0x766ec0, preferred VA 0x11066ec0. It
// returns 1 when its argument equals the word at 0x10 or at 0x18, or the word at 0x8 of any node of
// the singly linked list at 0x20, and 0 otherwise. The class, method and member names are
// invented; the offset and the bytes are the binary's.

struct UnkType_11066ec0_Node
{
    UnkType_11066ec0_Node* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_11066ec0
{
public:
    int Unk_11066ec0(int Value);

    unsigned char unk_0[0x10];
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1c;
    UnkType_11066ec0_Node* unk_20;
};

// UnkType_11066ec0::Unk_11066ec0
int UnkType_11066ec0::Unk_11066ec0(int Value)
{
    UnkType_11066ec0_Node* Node;

    if ( Value == unk_10 || Value == unk_18 )
    {
        return 1;
    }
    for ( Node = unk_20; Node != 0; Node = Node->unk_0 )
    {
        if ( Node->unk_8 == Value )
        {
            return 1;
        }
    }
    return 0;
}
