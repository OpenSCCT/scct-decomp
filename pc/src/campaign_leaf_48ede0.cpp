// campaign_leaf_48ede0.cpp -- thiscall method at VA 0x10d8ede0. It releases the object at 0x00,
// if any, through its method at 0x10d8eb50 when the flag at 0x08 is set or 0x10d86130 otherwise,
// and clears 0x00. Given an item, it then copies the item's word at 0x2c to 0x04 (reporting the
// code 0xe000000e through 0x10d977f0 and storing 0 when the low 22 bits of that word are zero)
// and passes the item to its own method at 0x10d8ec20. It returns this. The class, method and
// member names are invented.

struct UnkType_10d8ede0_Item
{
    unsigned char unk_0[0x2c];
    unsigned int unk_2c;
};

class UnkType_10d8ede0_Target
{
public:
    void Unk_10d86130();
    void Unk_10d8eb50();
};

void Unk_10d977f0(int First, int Second, unsigned int Code, int Fourth);

class UnkType_10d8ede0
{
public:
    UnkType_10d8ede0& Unk_10d8ede0(UnkType_10d8ede0_Item* Item);
    void Unk_10d8ec20(UnkType_10d8ede0_Item* Item);

private:
    UnkType_10d8ede0_Target* unk_0;
    unsigned int unk_4;
    bool unk_8;
};

// UnkType_10d8ede0::Unk_10d8ede0
UnkType_10d8ede0& UnkType_10d8ede0::Unk_10d8ede0(UnkType_10d8ede0_Item* Item)
{
    unsigned int Value;

    if ( unk_0 )
    {
        if ( unk_8 )
        {
            unk_0->Unk_10d8eb50();
        }
        else
        {
            unk_0->Unk_10d86130();
        }
        unk_0 = 0;
    }
    if ( Item )
    {
        Value = Item->unk_2c;
        if ( ( Value & 0x3fffff ) == 0 )
        {
            Unk_10d977f0(0, 0, 0xe000000e, 0);
            Value = 0;
        }
        unk_4 = Value;
        Unk_10d8ec20(Item);
    }
    return *this;
}
