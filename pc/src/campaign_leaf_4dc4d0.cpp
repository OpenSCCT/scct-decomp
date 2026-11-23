// campaign_leaf_4dc4d0.cpp -- one function at file offset 0x4dc4d0, preferred VA 0x10ddc4d0.
// When the method at 0x10d95310 of Item returns true it calls the method at 0x10d94d70 of Item,
// passes the int at offset 0x50 of Item to the method at 0x10d9e850 of Target and returns true;
// otherwise it returns false. The function, class, method, member and parameter names are
// invented; the offset and the bytes are the binary's.

class UnkType_10ddc4d0_Target
{
public:
    void Unk_10d9e850(int Value);
};

class UnkType_10ddc4d0_Item
{
public:
    unsigned char unk_0[0x50];
    int unk_50;

    bool Unk_10d95310();
    void Unk_10d94d70();
};

// Unk_10ddc4d0
bool Unk_10ddc4d0(UnkType_10ddc4d0_Target* Target, UnkType_10ddc4d0_Item* Item)
{
    if ( !Item->Unk_10d95310() )
    {
        return false;
    }
    Item->Unk_10d94d70();
    Target->Unk_10d9e850(Item->unk_50);
    return true;
}
