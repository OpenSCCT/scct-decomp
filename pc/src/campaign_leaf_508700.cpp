// campaign_leaf_508700.cpp -- method at VA 0x10e08700: appends a copy of its sixteen-byte argument
// to the array at 0x10 (data, count, capacity in the low 31 bits), growing it through the function
// at VA 0x10dfc430 when full, and returns the new entry's index. The class, method and member names
// are invented; the offsets and the address are the binary's.

class UnkType_10e08700_Item
{
public:
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
};

class UnkType_10e08700_Array;

void Unk_10dfc430(UnkType_10e08700_Array* Array, int ElementSize);

class UnkType_10e08700_Array
{
public:
    void Add(const UnkType_10e08700_Item& Item)
    {
        if ( Num == ( Max & 0x7fffffff ) )
        {
            Unk_10dfc430(this, sizeof(UnkType_10e08700_Item));
        }
        UnkType_10e08700_Item* Slot = &Data[Num];
        Num++;
        *Slot = Item;
    }

    UnkType_10e08700_Item* Data;
    int Num;
    int Max;
};

class UnkType_10e08700
{
public:
    int Unk_10e08700(const UnkType_10e08700_Item& Item);

    unsigned char unk_00[0x10];
    UnkType_10e08700_Array unk_10;
};

// UnkType_10e08700::Unk_10e08700
int UnkType_10e08700::Unk_10e08700(const UnkType_10e08700_Item& Item)
{
    int Index = unk_10.Num;
    unk_10.Add(Item);
    return Index;
}
