// campaign_leaf_557a40.cpp -- thiscall method at VA 0x10e57a40. With the byte at 0x12c set to 1
// for the duration, it numbers Item (the word at 0x20) from the counter at 0x134 counting down when
// Item's byte at 0x40 is set, or from the counter at 0x130 counting up otherwise, then passes Item
// to the methods at VA 0x10e53b10 and VA 0x10e55b50. It then restores the byte, counts a reference
// on Item (the word at 6), passes this object and Item to VA 0x10e667b0 and returns Item. All names
// are invented; the addresses are the binary's.

class UnkType_10e57a40;
struct UnkType_10e57a40_Item;

void Unk_10e667b0(UnkType_10e57a40* Owner, UnkType_10e57a40_Item* Item);

struct UnkType_10e57a40_Item
{
    int unk_00;
    short unk_04;
    short unk_06;
    int unk_08[6];
    int unk_20;
    int unk_24[7];
    unsigned char unk_40;
};

class UnkType_10e57a40
{
public:
    UnkType_10e57a40_Item* Unk_10e57a40(UnkType_10e57a40_Item* Item);

private:
    void Unk_10e53b10(UnkType_10e57a40_Item* Item);
    void Unk_10e55b50(UnkType_10e57a40_Item* Item);

    int unk_00[0x12c / 4];
    char unk_12c;
    int unk_130;
    int unk_134;
};

// UnkType_10e57a40::Unk_10e57a40
UnkType_10e57a40_Item* UnkType_10e57a40::Unk_10e57a40(UnkType_10e57a40_Item* Item)
{
    int Saved = unk_12c;

    unk_12c = 1;
    Item->unk_20 = Item->unk_40 ? unk_134-- : unk_130++;
    Unk_10e53b10(Item);
    Unk_10e55b50(Item);
    unk_12c = Saved;
    Item->unk_06++;
    Unk_10e667b0(this, Item);
    return Item;
}
