// campaign_leaf_266e60.cpp -- a member function at VA 0x10b66e60 taking an object pointer: it
// returns false when the pointer is null. Otherwise, when the object's pointer at 0x04 is set, it
// has that object's virtual slot 5 fill a local pair of 16-bit values (cleared beforehand), clears
// each value that is not zero and passes the pair to virtual slot 6. It returns true. The class,
// method, member and parameter names are invented; the offsets and slots are the binary's.

class UnkType_10b66e60_Pair
{
public:
    short unk_00;
    short unk_02;
};

class UnkType_10b66e60_Target
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5(UnkType_10b66e60_Pair* Pair);
    virtual void VirtualSlot6(UnkType_10b66e60_Pair* Pair);
};

class UnkType_10b66e60_Item
{
public:
    int unk_00;
    UnkType_10b66e60_Target* unk_04;
};

class UnkType_10b66e60
{
public:
    bool Unk_10b66e60(UnkType_10b66e60_Item* Item);
};

// UnkType_10b66e60::Unk_10b66e60
bool UnkType_10b66e60::Unk_10b66e60(UnkType_10b66e60_Item* Item)
{
    if ( !Item )
    {
        return false;
    }
    UnkType_10b66e60_Target* Target = Item->unk_04;
    UnkType_10b66e60_Pair Pair;
    Pair.unk_00 = 0;
    Pair.unk_02 = 0;
    if ( Target )
    {
        Target->VirtualSlot5(&Pair);
        if ( Pair.unk_00 != 0 )
        {
            Pair.unk_00 = 0;
        }
        if ( Pair.unk_02 != 0 )
        {
            Pair.unk_02 = 0;
        }
        Target->VirtualSlot6(&Pair);
    }
    return true;
}
