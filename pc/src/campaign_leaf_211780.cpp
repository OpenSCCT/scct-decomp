// campaign_leaf_211780.cpp -- a member function at VA 0x10b11780 that calls the free function at VA
// 0x10ea9884 with the int at 0x24 of the object its argument points to, the int at 0x00 of this,
// and the int at 0x20 of the argument's object. The class, method and member names are invented;
// the offsets and addresses are the binary's.

void Unk_10ea9884(int First, int Second, int Third);

class UnkType_10b11780_Item
{
public:
    unsigned char unk_00[0x20];
    int unk_20;
    int unk_24;
};

class UnkType_10b11780
{
public:
    void Unk_10b11780(UnkType_10b11780_Item* Item);

private:
    int unk_00;
};

// UnkType_10b11780::Unk_10b11780
void UnkType_10b11780::Unk_10b11780(UnkType_10b11780_Item* Item)
{
    Unk_10ea9884(Item->unk_24, unk_00, Item->unk_20);
}
