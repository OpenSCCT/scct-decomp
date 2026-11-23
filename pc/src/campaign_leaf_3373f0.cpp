// campaign_leaf_3373f0.cpp -- one function at file offset 0x3373f0, preferred VA 0x10c373f0. It
// clears the word at 0x74 and walks the list at 0x34 (next at 0x4, listener at 0x8): when the word
// at 0xc of Message is clear it sets the byte at 0x4e and passes Message's words at 0x10 and 0x14
// to each listener's virtual slot 2, otherwise its words at 0xc, 0x10 and 0x14 to slot 3. Then it
// passes Message's block at 0x10 and Message itself to the function at 0x109014a0 and returns 0.
// The class, function, member, slot, local and parameter names are invented; the offsets and the
// bytes are the binary's.

void Unk_109014a0(void* Block);

class UnkType_10c373f0_Listener
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2(void* Data, int Size);
    virtual void VirtualSlot3(int Kind, void* Data, int Size);
};

class UnkType_10c373f0_Node
{
public:
    int unk_0;
    UnkType_10c373f0_Node* unk_4;
    UnkType_10c373f0_Listener* unk_8;
};

class UnkType_10c373f0_Message
{
public:
    unsigned char unk_0[0xc];
    int unk_c;
    void* unk_10;
    int unk_14;
};

class UnkType_10c373f0
{
public:
    int Unk_10c373f0(UnkType_10c373f0_Message* Message);

    unsigned char unk_0[0x34];
    UnkType_10c373f0_Node* unk_34;
    unsigned char unk_38[0x16];
    unsigned char unk_4e;
    unsigned char unk_4f[0x25];
    int unk_74;
};

// UnkType_10c373f0::Unk_10c373f0
int UnkType_10c373f0::Unk_10c373f0(UnkType_10c373f0_Message* Message)
{
    UnkType_10c373f0_Node* Node;

    unk_74 = 0;
    if ( Message->unk_c == 0 )
    {
        unk_4e = 1;
        for ( Node = unk_34; Node != 0; Node = Node->unk_4 )
        {
            Node->unk_8->VirtualSlot2(Message->unk_10, Message->unk_14);
        }
    }
    else
    {
        for ( Node = unk_34; Node != 0; Node = Node->unk_4 )
        {
            Node->unk_8->VirtualSlot3(Message->unk_c, Message->unk_10, Message->unk_14);
        }
    }
    Unk_109014a0(Message->unk_10);
    Unk_109014a0(Message);
    return 0;
}
