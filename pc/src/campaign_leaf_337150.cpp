// campaign_leaf_337150.cpp -- one function at file offset 0x337150, preferred VA 0x10c37150. For
// each node of the list at 0x8c (head at 0x4; each node has its next node at 0x4 and its entry at
// 0x8) it releases the entry's interfaces at 0x8 and 0x4 through stdcall virtual slot 2, frees the
// blocks at 0x10, 0x54, 0x50 and 0x60 and the entry itself through the function at 0x109014a0;
// it ends with the list's method at 0x10c37e70. The class, function, method, structure, member
// and local names are invented; the offsets, the slot and the bytes are the binary's.

void Unk_109014a0(void* Block);

class UnkType_10c37150_Interface
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual unsigned long __stdcall VirtualSlot2();
};

struct UnkType_10c37150_Entry
{
    int unk_0;
    UnkType_10c37150_Interface* unk_4;
    UnkType_10c37150_Interface* unk_8;
    int unk_c;
    void* unk_10;
    unsigned char unk_14[0x3c];
    void* unk_50;
    void* unk_54;
    unsigned char unk_58[0x8];
    void* unk_60;
};

struct UnkType_10c37150_Node
{
    UnkType_10c37150_Node* unk_0;
    UnkType_10c37150_Node* unk_4;
    UnkType_10c37150_Entry* unk_8;
};

class UnkType_10c37150_List
{
public:
    virtual void VirtualSlot0();
    void Unk_10c37e70();

    UnkType_10c37150_Node* unk_4;
    UnkType_10c37150_Node* unk_8;
};

class UnkType_10c37150
{
public:
    void Unk_10c37150();

    unsigned char unk_0[0x8c];
    UnkType_10c37150_List unk_8c;
};

// UnkType_10c37150::Unk_10c37150
void UnkType_10c37150::Unk_10c37150()
{
    UnkType_10c37150_Node* Node;

    for ( Node = unk_8c.unk_4; Node != 0; Node = Node->unk_4 )
    {
        UnkType_10c37150_Entry* Entry = Node->unk_8;

        if ( Entry != 0 )
        {
            Entry->unk_8->VirtualSlot2();
            Entry->unk_4->VirtualSlot2();
            Unk_109014a0(Entry->unk_10);
            Unk_109014a0(Entry->unk_54);
            Unk_109014a0(Entry->unk_50);
            Unk_109014a0(Entry->unk_60);
            Unk_109014a0(Entry);
        }
    }
    unk_8c.Unk_10c37e70();
}
