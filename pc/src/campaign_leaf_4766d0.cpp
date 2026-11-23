// campaign_leaf_4766d0.cpp -- thiscall method at VA 0x10d766d0. It builds a local polymorphic
// object from its two arguments and walks the list whose first node is at 0x48, passing the
// object to the method at 0x10d75a90 of each node's item; it returns 0 at the first item that
// accepts it, else 1. The class, method and parameter names are invented.

class UnkType_10d766d0_Query
{
public:
    UnkType_10d766d0_Query(int First, int Second) : unk_4(First), unk_8(Second) {}
    virtual void VirtualSlot0();

private:
    int unk_4;
    int unk_8;
    int unk_c;
};

class UnkType_10d766d0_Item
{
public:
    int Unk_10d75a90(UnkType_10d766d0_Query* Query);
};

struct UnkType_10d766d0_Node
{
    UnkType_10d766d0_Node* unk_0;
    int unk_4;
    UnkType_10d766d0_Item* unk_8;
};

class UnkType_10d766d0
{
public:
    int Unk_10d766d0(int First, int Second);

private:
    unsigned char unk_0[0x48];
    UnkType_10d766d0_Node* unk_48;
};

// UnkType_10d766d0::Unk_10d766d0
int UnkType_10d766d0::Unk_10d766d0(int First, int Second)
{
    UnkType_10d766d0_Query Query(First, Second);
    UnkType_10d766d0_Node* Next;
    UnkType_10d766d0_Node* Node;

    Next = unk_48;
    while ( Next )
    {
        Node = Next;
        Next = Next->unk_0;
        if ( Node->unk_8->Unk_10d75a90(&Query) )
        {
            return 0;
        }
    }
    return 1;
}
