// campaign_leaf_3d7b30.cpp -- one function at file offset 0x3d7b30, preferred VA 0x10cd7b30. It
// looks Key up in two 128-bucket hash tables of chained nodes (bucket heads at 0x84, key at
// 0x20, next node at 0x30): first in the table reached through the pointers at 0xc and 0x1c,
// unless Skip is set, then in the table at 0x24. It returns the node, or null. The class,
// method, structure, member and parameter names are invented; the offsets and the bytes are the
// binary's.

struct UnkType_10cd7b30_Node
{
    unsigned char unk_0[0x20];
    int unk_20;
    unsigned char unk_24[0xc];
    UnkType_10cd7b30_Node* unk_30;
};

struct UnkType_10cd7b30_Table
{
    unsigned char unk_0[0x84];
    UnkType_10cd7b30_Node* unk_84[128];
};

struct UnkType_10cd7b30_Parent
{
    unsigned char unk_0[0x1c];
    UnkType_10cd7b30_Table* unk_1c;
};

class UnkType_10cd7b30
{
public:
    UnkType_10cd7b30_Node* Unk_10cd7b30(int Key, int Skip) const;

    unsigned char unk_0[0xc];
    UnkType_10cd7b30_Parent* unk_c;
    unsigned char unk_10[0x14];
    UnkType_10cd7b30_Table* unk_24;
};

// UnkType_10cd7b30::Unk_10cd7b30
UnkType_10cd7b30_Node* UnkType_10cd7b30::Unk_10cd7b30(int Key, int Skip) const
{
    int Bucket = Key & 0x7f;
    UnkType_10cd7b30_Node* Node;

    if ( unk_c != 0 && unk_c->unk_1c != 0 && !Skip )
    {
        for ( Node = unk_c->unk_1c->unk_84[Bucket]; Node != 0; Node = Node->unk_30 )
        {
            if ( Node->unk_20 == Key )
            {
                return Node;
            }
        }
    }
    for ( Node = unk_24->unk_84[Bucket]; Node != 0; Node = Node->unk_30 )
    {
        if ( Node->unk_20 == Key )
        {
            return Node;
        }
    }
    return 0;
}
