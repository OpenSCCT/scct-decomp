// campaign_leaf_5580e0.cpp -- thiscall method at VA 0x10e580e0. While the byte at 0x12c is 1, it
// appends Item to the pointer array at 0xf0 (growing it through VA 0x10dfc430), counts a reference
// on Item (the word at 6) and sets Handled to false. Otherwise it calls the method at VA 0x10e57ee0
// when the word at 0x24 is positive, passes Item to the method at VA 0x10e56060, calls Item's
// method at VA 0x10e54b90, passes Item to the method at VA 0x10e561e0 and sets Handled to true. It
// returns Handled. All names are invented; the addresses are the binary's.

struct UnkType_10e580e0_Item;
struct UnkType_10e580e0_Array;

void Unk_10dfc430(UnkType_10e580e0_Array* Array, int ElementSize);

struct UnkType_10e580e0_Array
{
    UnkType_10e580e0_Item** unk_00;
    int unk_04;
    int unk_08;

    // UnkType_10e580e0_Array::Add
    // guess: appends one pointer, growing the storage through VA 0x10dfc430 when it is full.
    void Add(UnkType_10e580e0_Item* Item)
    {
        if ( unk_04 == ( unk_08 & 0x7fffffff ) )
        {
            Unk_10dfc430(this, 4);
        }
        unk_00[unk_04] = Item;
        unk_04++;
    }
};

struct UnkType_10e580e0_Item
{
    void Unk_10e54b90();

    int unk_00;
    short unk_04;
    short unk_06;
};

class UnkType_10e580e0
{
public:
    bool* Unk_10e580e0(bool* Handled, UnkType_10e580e0_Item* Item);

private:
    void Unk_10e57ee0();
    void Unk_10e56060(UnkType_10e580e0_Item* Item);
    void Unk_10e561e0(UnkType_10e580e0_Item* Item);

    int unk_00[9];
    int unk_24;
    int unk_28[0xc8 / 4];
    UnkType_10e580e0_Array unk_f0;
    int unk_fc[0x30 / 4];
    unsigned char unk_12c;
};

// UnkType_10e580e0::Unk_10e580e0
bool* UnkType_10e580e0::Unk_10e580e0(bool* Handled, UnkType_10e580e0_Item* Item)
{
    if ( unk_12c == 1 )
    {
        unk_f0.Add(Item);
        Item->unk_06++;
        *Handled = false;
        return Handled;
    }
    if ( unk_24 > 0 )
    {
        Unk_10e57ee0();
    }
    Unk_10e56060(Item);
    Item->Unk_10e54b90();
    Unk_10e561e0(Item);
    *Handled = true;
    return Handled;
}
