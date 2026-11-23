// campaign_leaf_553c10.cpp -- thiscall method at VA 0x10e53c10. While the byte at 0x12c is 1, it
// appends Item to the pointer array at 0xfc (growing it through VA 0x10dfc430), counts a reference
// on Item (the word at 6) and sets Handled to false. Otherwise it picks the object at 0x44 of the
// object at 0x0c of Item, or of the one at 0x10 when the first one's word at 0x24 is -1, passes
// this object and Item to VA 0x10e669e0, hands Item to the picked object's second virtual method
// and sets Handled to true. It returns Handled. All names are invented; the addresses are the
// binary's.

class UnkType_10e53c10;
struct UnkType_10e53c10_Item;
struct UnkType_10e53c10_Array;

void Unk_10dfc430(UnkType_10e53c10_Array* Array, int ElementSize);
void Unk_10e669e0(UnkType_10e53c10* Owner, UnkType_10e53c10_Item* Item);

struct UnkType_10e53c10_Array
{
    UnkType_10e53c10_Item** unk_00;
    int unk_04;
    int unk_08;

    // UnkType_10e53c10_Array::Add
    // guess: appends one pointer, growing the storage through VA 0x10dfc430 when it is full.
    void Add(UnkType_10e53c10_Item* Item)
    {
        if ( unk_04 == ( unk_08 & 0x7fffffff ) )
        {
            Unk_10dfc430(this, 4);
        }
        unk_00[unk_04] = Item;
        unk_04++;
    }
};

class UnkType_10e53c10_Target
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1(UnkType_10e53c10_Item* Item);

private:
    int unk_04[8];

public:
    int unk_24;
};

struct UnkType_10e53c10_Side
{
    int unk_00[17];
    UnkType_10e53c10_Target* unk_44;
};

struct UnkType_10e53c10_Item
{
    int unk_00;
    short unk_04;
    short unk_06;
    int unk_08;
    UnkType_10e53c10_Side* unk_0c;
    UnkType_10e53c10_Side* unk_10;
};

class UnkType_10e53c10
{
public:
    bool* Unk_10e53c10(bool* Handled, UnkType_10e53c10_Item* Item);

private:
    int unk_00[0xfc / 4];
    UnkType_10e53c10_Array unk_fc;
    int unk_108[9];
    unsigned char unk_12c;
};

// UnkType_10e53c10::Unk_10e53c10
bool* UnkType_10e53c10::Unk_10e53c10(bool* Handled, UnkType_10e53c10_Item* Item)
{
    if ( unk_12c == 1 )
    {
        unk_fc.Add(Item);
        Item->unk_06++;
        *Handled = false;
        return Handled;
    }

    UnkType_10e53c10_Target* Target = Item->unk_0c->unk_44;

    if ( Target->unk_24 == -1 )
    {
        Target = Item->unk_10->unk_44;
    }
    Unk_10e669e0(this, Item);
    Target->VirtualSlot1(Item);
    *Handled = true;
    return Handled;
}
