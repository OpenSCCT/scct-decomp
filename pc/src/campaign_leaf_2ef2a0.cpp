// campaign_leaf_2ef2a0.cpp -- a member function at VA 0x10bef2a0 that passes its two arguments to
// the member at VA 0x10beafa0 and then copies the byte at 0x08 of the object its second argument
// points to into the byte at 0x3fc. The class, method and member names are invented; the offsets
// and addresses are the binary's.

class UnkType_10bef2a0_Item
{
public:
    int unk_00;
    int unk_04;
    unsigned char unk_08;
};

class UnkType_10bef2a0
{
public:
    void Unk_10beafa0(int Value, UnkType_10bef2a0_Item* Item);
    void Unk_10bef2a0(int Value, UnkType_10bef2a0_Item* Item);

private:
    unsigned char unk_000[0x3fc];
    unsigned char unk_3fc;
};

// UnkType_10bef2a0::Unk_10bef2a0
void UnkType_10bef2a0::Unk_10bef2a0(int Value, UnkType_10bef2a0_Item* Item)
{
    Unk_10beafa0(Value, Item);
    unk_3fc = Item->unk_08;
}
