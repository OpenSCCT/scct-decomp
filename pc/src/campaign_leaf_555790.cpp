// campaign_leaf_555790.cpp -- thiscall method at VA 0x10e55790: takes the end of Link that is not
// the object at 0x04 (each end points at the part at 0x10 of a node), and unless the byte at 0x40
// of that node's object at 0x20 is set, passes Link to the method at VA 0x10e55820 of that object's
// owner (0x44) and adds the owner to the pointer array at 0x08 when it is not already there
// (growing it through VA 0x10dfc430). All names are invented; the addresses are the binary's.

struct UnkType_10e55790_Link;
class UnkType_10e55790_Owner;
struct UnkType_10e55790_Array;

void Unk_10dfc430(UnkType_10e55790_Array* Array, int ElementSize);

class UnkType_10e55790_Owner
{
public:
    void Unk_10e55820(UnkType_10e55790_Link* Link);
};

struct UnkType_10e55790_State
{
    int unk_00[16];
    unsigned char unk_40;
    UnkType_10e55790_Owner* unk_44;
};

struct UnkType_10e55790_Front
{
    int unk_00[4];
};

struct UnkType_10e55790_End
{
    int unk_00[4];
};

struct UnkType_10e55790_Node : public UnkType_10e55790_Front, public UnkType_10e55790_End
{
    UnkType_10e55790_State* unk_20;
};

struct UnkType_10e55790_Link
{
    UnkType_10e55790_End* unk_00;
    UnkType_10e55790_End* unk_04;
};

struct UnkType_10e55790_Array
{
    UnkType_10e55790_Owner** unk_00;
    int unk_04;
    int unk_08;

    // UnkType_10e55790_Array::Find
    // guess: returns the index of Item, or -1.
    int Find(UnkType_10e55790_Owner* Item)
    {
        for ( int Index = 0; Index < unk_04; Index++ )
        {
            if ( unk_00[Index] == Item )
            {
                return Index;
            }
        }
        return -1;
    }

    // UnkType_10e55790_Array::Add
    // guess: appends one pointer, growing the storage through VA 0x10dfc430 when it is full.
    void Add(UnkType_10e55790_Owner* Item)
    {
        if ( unk_04 == ( unk_08 & 0x7fffffff ) )
        {
            Unk_10dfc430(this, 4);
        }
        unk_00[unk_04] = Item;
        unk_04++;
    }
};

class UnkType_10e55790
{
public:
    void Unk_10e55790(UnkType_10e55790_Link* Link);

private:
    int unk_00;
    UnkType_10e55790_Node* unk_04;
    UnkType_10e55790_Array unk_08;
};

// UnkType_10e55790::Unk_10e55790
void UnkType_10e55790::Unk_10e55790(UnkType_10e55790_Link* Link)
{
    UnkType_10e55790_End* Self = unk_04;
    UnkType_10e55790_End* Other = Link->unk_00 == Self ? Link->unk_04 : Link->unk_00;

    UnkType_10e55790_State* State = static_cast<UnkType_10e55790_Node*>(Other)->unk_20;

    if ( State->unk_40 )
    {
        return;
    }

    UnkType_10e55790_Owner* Owner = State->unk_44;

    Owner->Unk_10e55820(Link);
    if ( unk_08.Find(Owner) == -1 )
    {
        unk_08.Add(Owner);
    }
}
