// campaign_leaf_08b180.cpp -- method at VA 0x1098b180: increments the 16-bit count at 0x06 of the
// object its argument points to and appends the pointer to the array at 0x18 (count at 0x1c,
// capacity in the low 31 bits of 0x20), first growing it through the free function at VA 0x10dfc430
// when it is full. The class, member and function names are invented; the offsets, the mask, the
// size and the address are the binary's.

class UnkType_1098b180_Item
{
public:
    virtual ~UnkType_1098b180_Item();

    unsigned short unk_04;
    unsigned short unk_06;
};

class UnkType_10dfc430_08b180;

void Unk_10dfc430(UnkType_10dfc430_08b180* Array, int ElementSize);

class UnkType_10dfc430_08b180
{
public:
    void Add(UnkType_1098b180_Item* Item)
    {
        if ( unk_04 == (int)(unk_08 & 0x7fffffff) )
        {
            Unk_10dfc430(this, sizeof(UnkType_1098b180_Item*));
        }
        unk_00[unk_04] = Item;
        unk_04++;
    }

private:
    UnkType_1098b180_Item** unk_00;
    int unk_04;
    unsigned int unk_08;
};

class UnkType_1098b180
{
public:
    void Unk_1098b180(UnkType_1098b180_Item* Item);

private:
    unsigned char unk_00[0x18];
    UnkType_10dfc430_08b180 unk_18;
};

// UnkType_1098b180::Unk_1098b180
void UnkType_1098b180::Unk_1098b180(UnkType_1098b180_Item* Item)
{
    Item->unk_06++;
    unk_18.Add(Item);
}
