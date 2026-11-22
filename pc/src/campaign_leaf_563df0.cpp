// campaign_leaf_563df0.cpp -- thiscall method at VA 0x10e63df0: the inverse of VA 0x10e64c00. It
// removes the object it is given from the pointer array at 0x3c by moving the last element into its
// slot (index at 0x58 of each object), clears the object's owner (0x44) and index, passes the
// negated result of the sixth virtual method of the object's member at 0x3c to the fifth virtual
// method of this object and sets the byte at 0x28. The class and method names are invented.

struct UnkType_10e64c00_Array;
struct UnkType_10e64c00_Item;

void Unk_10dfc430(UnkType_10e64c00_Array* Array, int ElementSize);

struct UnkType_10e64c00_Array
{
    UnkType_10e64c00_Item** unk_00;
    int unk_04;
    int unk_08;

    // UnkType_10e64c00_Array::Add
    // guess: appends one pointer, growing the storage through VA 0x10dfc430 when it is full.
    void Add(UnkType_10e64c00_Item* Item)
    {
        if ( unk_04 == ( unk_08 & 0x7fffffff ) )
        {
            Unk_10dfc430(this, 4);
        }
        unk_00[unk_04] = Item;
        unk_04++;
    }
};

class UnkType_10e64c00_3c
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual int VirtualSlot5();
};

class UnkType_10e64c00;

struct UnkType_10e64c00_Item
{
    int unk_00[15];
    UnkType_10e64c00_3c* unk_3c;
    int unk_40;
    UnkType_10e64c00* unk_44;
    int unk_48[4];
    int unk_58;
};

class UnkType_10e64c00
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4(int Value);

    void Unk_10e63df0(UnkType_10e64c00_Item* Item);
    void Unk_10e64c00(UnkType_10e64c00_Item* Item);

private:
    int unk_04[9];
    unsigned char unk_28;
    unsigned char unk_29;
    unsigned char unk_2a;
    unsigned char unk_2b;
    int unk_2c[4];
    UnkType_10e64c00_Array unk_3c;
};

// UnkType_10e64c00::Unk_10e63df0
void UnkType_10e64c00::Unk_10e63df0(UnkType_10e64c00_Item* Item)
{
    unk_3c.unk_00[Item->unk_58] = unk_3c.unk_00[unk_3c.unk_04 - 1];
    unk_3c.unk_00[Item->unk_58]->unk_58 = Item->unk_58;
    unk_3c.unk_04--;
    Item->unk_44 = 0;
    Item->unk_58 = -1;
    VirtualSlot4(-Item->unk_3c->VirtualSlot5());
    unk_28 = 1;
}
