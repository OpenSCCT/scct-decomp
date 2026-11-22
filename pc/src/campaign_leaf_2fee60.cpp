// campaign_leaf_2fee60.cpp -- a member function at VA 0x10bfee60 that passes the int at 0x2c8 to
// the member at VA 0x1099e460 of the object at 0x400 of the object its argument points to. The
// class, method and member names are invented; the offsets and addresses are the binary's.

class UnkType_1099e460
{
public:
    void Unk_1099e460(int Value);
};

class UnkType_10bfee60_Item
{
public:
    unsigned char unk_000[0x400];
    UnkType_1099e460* unk_400;
};

class UnkType_10bfee60
{
public:
    void Unk_10bfee60(UnkType_10bfee60_Item* Item);

private:
    unsigned char unk_000[0x2c8];
    int unk_2c8;
};

// UnkType_10bfee60::Unk_10bfee60
void UnkType_10bfee60::Unk_10bfee60(UnkType_10bfee60_Item* Item)
{
    Item->unk_400->Unk_1099e460(unk_2c8);
}
