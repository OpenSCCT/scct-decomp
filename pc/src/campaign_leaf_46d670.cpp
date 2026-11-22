// campaign_leaf_46d670.cpp -- one function at file offset 0x46d670, preferred VA 0x10d6d670. It
// walks the singly linked list at 0x138 and returns the first node's object (at 0x8) whose words
// at 0x78 and 0x74 equal the two arguments, or null. The class, method, structure and member
// names are invented; the offsets and the bytes are the binary's.

struct UnkType_10d6d670_Item
{
    unsigned char unk_0[0x74];
    int unk_74;
    int unk_78;
};

struct UnkType_10d6d670_Node
{
    UnkType_10d6d670_Node* unk_0;
    int unk_4;
    UnkType_10d6d670_Item* unk_8;
};

class UnkType_10d6d670
{
public:
    UnkType_10d6d670_Item* Unk_10d6d670(int First, int Second) const;

    unsigned char unk_0[0x138];
    UnkType_10d6d670_Node* unk_138;
};

// UnkType_10d6d670::Unk_10d6d670
UnkType_10d6d670_Item* UnkType_10d6d670::Unk_10d6d670(int First, int Second) const
{
    UnkType_10d6d670_Node* Node = unk_138;

    while ( Node != 0 )
    {
        UnkType_10d6d670_Node* Current = Node;
        UnkType_10d6d670_Item* Item;

        Node = Node->unk_0;
        Item = Current->unk_8;
        if ( Item->unk_78 == First && Item->unk_74 == Second )
        {
            return Item;
        }
    }
    return 0;
}
