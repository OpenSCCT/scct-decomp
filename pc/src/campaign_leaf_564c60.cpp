// campaign_leaf_564c60.cpp -- thiscall method at VA 0x10e64c60: appends the object it is given to
// the pointer array at 0x58, fills a 16-byte record through the object's eleventh virtual method
// and passes both to this object's third virtual method, then takes a reference to the object
// (count at 0x06) and makes this object its owner (member at 0x14). The class and method names are
// invented.

struct UnkType_10e64c60_Array;
class UnkType_10e64c60_Item;

void Unk_10dfc430(UnkType_10e64c60_Array* Array, int ElementSize);

struct UnkType_10e64c60_Array
{
    UnkType_10e64c60_Item** unk_00;
    int unk_04;
    int unk_08;

    // UnkType_10e64c60_Array::Add
    // guess: appends one pointer, growing the storage through VA 0x10dfc430 when it is full.
    void Add(UnkType_10e64c60_Item* Item)
    {
        if ( unk_04 == ( unk_08 & 0x7fffffff ) )
        {
            Unk_10dfc430(this, 4);
        }
        unk_00[unk_04] = Item;
        unk_04++;
    }
};

struct UnkType_10e64c60_Record
{
    int unk_00[4];
};

class UnkType_10e64c60;

class UnkType_10e64c60_Item
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void VirtualSlot9();
    virtual void VirtualSlot10(UnkType_10e64c60_Record* Record);

    short unk_04;
    short unk_06;
    int unk_08[3];
    UnkType_10e64c60* unk_14;
};

class UnkType_10e64c60
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2(UnkType_10e64c60_Item* Item, UnkType_10e64c60_Record* Record);

    void Unk_10e64c60(UnkType_10e64c60_Item* Item);

private:
    int unk_04[0x54 / 4];
    UnkType_10e64c60_Array unk_58;
};

// UnkType_10e64c60::Unk_10e64c60
void UnkType_10e64c60::Unk_10e64c60(UnkType_10e64c60_Item* Item)
{
    UnkType_10e64c60_Record Record;
    unk_58.Add(Item);
    Item->VirtualSlot10(&Record);
    VirtualSlot2(Item, &Record);
    Item->unk_06++;
    Item->unk_14 = this;
}
