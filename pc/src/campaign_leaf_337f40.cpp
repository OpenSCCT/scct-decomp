// campaign_leaf_337f40.cpp -- one function at file offset 0x337f40, preferred VA 0x10c37f40. For
// each node of Source's list (head at 0x4; each node has its next node at 0x4 and its value at
// 0x8) it allocates a 12-byte node through the function at 0x10901480, appends it with that
// value to this list (head at 0x4, tail at 0x8) and calls virtual slot 1; it returns this list.
// The class, function, structure, member, local and parameter names are invented; the offsets,
// the slot and the bytes are the binary's.

void* Unk_10901480(unsigned int Size);

struct UnkType_10c37f40_Node
{
    UnkType_10c37f40_Node* unk_0;
    UnkType_10c37f40_Node* unk_4;
    int unk_8;
};

class UnkType_10c37f40
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    UnkType_10c37f40& Unk_10c37f40(const UnkType_10c37f40& Source);

    UnkType_10c37f40_Node* unk_4;
    UnkType_10c37f40_Node* unk_8;
};

// UnkType_10c37f40::Unk_10c37f40
UnkType_10c37f40& UnkType_10c37f40::Unk_10c37f40(const UnkType_10c37f40& Source)
{
    UnkType_10c37f40_Node* Node;

    for ( Node = Source.unk_4; Node != 0; Node = Node->unk_4 )
    {
        int Value = Node->unk_8;
        UnkType_10c37f40_Node* Added = (UnkType_10c37f40_Node*)Unk_10901480(0xc);

        Added->unk_0 = 0;
        Added->unk_4 = 0;
        Added->unk_8 = Value;
        if ( unk_8 == 0 )
        {
            unk_4 = Added;
        }
        else
        {
            unk_8->unk_4 = Added;
            Added->unk_0 = unk_8;
        }
        unk_8 = Added;
        VirtualSlot1();
    }
    return *this;
}
