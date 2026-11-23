// campaign_leaf_235a40.cpp -- a member function at VA 0x10b35a40: it clears the first flag bit at
// 0x18 of every item of the array at 0x40 (count at 0x44); then, when the count at 0x5c is between
// 1 and that count, it passes each of the first that many items, the item before it (null for the
// first), 0 and the matching entry of the array at 0x58 to its own member at VA 0x10b357a0, links
// the first and last items (the first's pointer at 0x48 to the last and the last's pointer at 0x44
// to the first, or only clears the first's pointer at 0x44 when they are the same) and returns
// true. Otherwise it returns false. guess: chains the items into a ring. The class, method and
// member names are invented; the offsets and addresses are the binary's.

class UnkType_10b35a40_Item
{
public:
    unsigned char unk_00[0x18];
    unsigned char unk_18 : 1;
    unsigned char unk_19[0x44 - 0x19];
    UnkType_10b35a40_Item* unk_44;
    UnkType_10b35a40_Item* unk_48;
};

class UnkType_10b35a40
{
public:
    void Unk_10b357a0(UnkType_10b35a40_Item* Item, UnkType_10b35a40_Item* Previous, int Value,
                      int Entry);
    bool Unk_10b35a40();

private:
    unsigned char unk_00[0x40];
    UnkType_10b35a40_Item** unk_40;
    int unk_44;
    unsigned char unk_48[0x58 - 0x48];
    int* unk_58;
    int unk_5c;
};

// UnkType_10b35a40::Unk_10b35a40
bool UnkType_10b35a40::Unk_10b35a40()
{
    int i;
    for ( i = 0; i < unk_44; i++ )
    {
        unk_40[i]->unk_18 = 0;
    }
    if ( unk_5c > 0 && unk_5c <= unk_44 )
    {
        UnkType_10b35a40_Item* Previous = 0;
        for ( i = 0; i < unk_5c; i++ )
        {
            UnkType_10b35a40_Item* Item = unk_40[i];
            Unk_10b357a0(Item, Previous, 0, unk_58[i]);
            Previous = Item;
        }
        UnkType_10b35a40_Item* First = unk_40[0];
        if ( Previous != First )
        {
            First->unk_48 = Previous;
            Previous->unk_44 = First;
        }
        else
        {
            First->unk_44 = 0;
        }
        return true;
    }
    return false;
}
