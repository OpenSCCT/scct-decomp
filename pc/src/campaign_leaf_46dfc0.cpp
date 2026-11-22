// campaign_leaf_46dfc0.cpp -- one function at file offset 0x46dfc0, preferred VA 0x10d6dfc0. It
// walks the singly linked list at 0x150 and, inside each node's object (at 0x8), its 0x18-byte
// entries (data at 0x28, count at 0x30) for one whose word at 0x10 equals Key; it stores that
// object through Owner and returns the entry's index. Key -2, and a failed search, return -2.
// The class, method, structure, member and parameter names are invented; the offsets and the
// bytes are the binary's.

struct UnkType_10d6dfc0_Entry
{
    unsigned char unk_0[0x10];
    int unk_10;
    unsigned char unk_14[0x4];
};

struct UnkType_10d6dfc0_Item
{
    unsigned char unk_0[0x28];
    UnkType_10d6dfc0_Entry* unk_28;
    int unk_2c;
    unsigned int unk_30;
};

struct UnkType_10d6dfc0_Node
{
    UnkType_10d6dfc0_Node* unk_0;
    int unk_4;
    UnkType_10d6dfc0_Item* unk_8;
};

class UnkType_10d6dfc0
{
public:
    int Unk_10d6dfc0(int Key, UnkType_10d6dfc0_Item** Owner) const;

    unsigned char unk_0[0x150];
    UnkType_10d6dfc0_Node* unk_150;
};

// UnkType_10d6dfc0::Unk_10d6dfc0
int UnkType_10d6dfc0::Unk_10d6dfc0(int Key, UnkType_10d6dfc0_Item** Owner) const
{
    UnkType_10d6dfc0_Node* Node;

    if ( Key == -2 )
    {
        return Key;
    }
    Node = unk_150;
    while ( Node != 0 )
    {
        UnkType_10d6dfc0_Node* Current = Node;
        UnkType_10d6dfc0_Item* Item;
        unsigned int Index;

        Node = Node->unk_0;
        Item = Current->unk_8;
        for ( Index = 0; Index < Item->unk_30; Index++ )
        {
            if ( Item->unk_28[Index].unk_10 == Key )
            {
                *Owner = Item;
                return Index;
            }
        }
    }
    return -2;
}
