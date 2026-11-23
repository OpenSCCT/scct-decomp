// campaign_leaf_338b80.cpp -- one function at file offset 0x338b80, preferred VA 0x10c38b80. For
// a Message whose word at 0x4 is not negative it sets the byte at 0xaa and calls virtual slot 5
// of the object at 0x8 of every node of the list at 0x34 (next node at 0x4); otherwise it passes
// that word to virtual slot 6 of each of them and clears the bytes at 0xaa and 0xa9. It then
// clears the word at 0x74, frees Message through the function at 0x109014a0 and returns 0. The
// class, function, structure, member, local and parameter names are invented; the offsets, the
// slots and the bytes are the binary's.

void Unk_109014a0(void* Block);

class UnkType_10c38b80_Listener
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6(int Value);
};

struct UnkType_10c38b80_Node
{
    UnkType_10c38b80_Node* unk_0;
    UnkType_10c38b80_Node* unk_4;
    UnkType_10c38b80_Listener* unk_8;
};

struct UnkType_10c38b80_Message
{
    int unk_0;
    int unk_4;
};

class UnkType_10c38b80
{
public:
    int Unk_10c38b80(UnkType_10c38b80_Message* Message);

    unsigned char unk_0[0x34];
    UnkType_10c38b80_Node* unk_34;
    unsigned char unk_38[0x3c];
    int unk_74;
    unsigned char unk_78[0x31];
    unsigned char unk_a9;
    unsigned char unk_aa;
};

// UnkType_10c38b80::Unk_10c38b80
int UnkType_10c38b80::Unk_10c38b80(UnkType_10c38b80_Message* Message)
{
    UnkType_10c38b80_Node* Node = unk_34;

    if ( Message->unk_4 >= 0 )
    {
        unk_aa = 1;
        for ( ; Node != 0; Node = Node->unk_4 )
        {
            Node->unk_8->VirtualSlot5();
        }
    }
    else
    {
        for ( ; Node != 0; Node = Node->unk_4 )
        {
            Node->unk_8->VirtualSlot6(Message->unk_4);
        }
        unk_aa = 0;
        unk_a9 = 0;
    }
    unk_74 = 0;
    Unk_109014a0(Message);
    return 0;
}
