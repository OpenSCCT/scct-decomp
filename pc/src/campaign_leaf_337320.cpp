// campaign_leaf_337320.cpp -- one function at file offset 0x337320, preferred VA 0x10c37320. When
// Message is set and its word at 0xc is negative, it clears the words at 0x9c and 0x74, passes
// Message to the function at 0x109014a0 and returns that word. Otherwise, when the word at 0x74
// is 1, it sets it to 2 and calls virtual slot 0 of the listener of each node of the list at 0x34
// (next at 0x4, listener at 0x8); then it clears the word at 0x9c, passes Message to the function
// at 0x109014a0 and returns 0. The class, function, member, slot, local and parameter names are
// invented; the offsets and the bytes are the binary's.

void Unk_109014a0(void* Block);

class UnkType_10c37320_Listener
{
public:
    virtual void VirtualSlot0();
};

class UnkType_10c37320_Node
{
public:
    int unk_0;
    UnkType_10c37320_Node* unk_4;
    UnkType_10c37320_Listener* unk_8;
};

class UnkType_10c37320_Message
{
public:
    unsigned char unk_0[0xc];
    int unk_c;
};

class UnkType_10c37320
{
public:
    int Unk_10c37320(UnkType_10c37320_Message* Message);

    unsigned char unk_0[0x34];
    UnkType_10c37320_Node* unk_34;
    unsigned char unk_38[0x3c];
    int unk_74;
    unsigned char unk_78[0x24];
    int unk_9c;
};

// UnkType_10c37320::Unk_10c37320
int UnkType_10c37320::Unk_10c37320(UnkType_10c37320_Message* Message)
{
    UnkType_10c37320_Node* Node;

    if ( Message != 0 && Message->unk_c < 0 )
    {
        unk_9c = 0;
        unk_74 = 0;
        Unk_109014a0(Message);
        return Message->unk_c;
    }
    switch ( unk_74 )
    {
    case 1:
        unk_74 = 2;
        for ( Node = unk_34; Node != 0; Node = Node->unk_4 )
        {
            Node->unk_8->VirtualSlot0();
        }
        break;
    }
    unk_9c = 0;
    Unk_109014a0(Message);
    return 0;
}
