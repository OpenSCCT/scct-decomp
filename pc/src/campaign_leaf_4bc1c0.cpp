// campaign_leaf_4bc1c0.cpp -- one function at file offset 0x4bc1c0, preferred VA 0x10dbc1c0.
// It returns the object the function at 0x10dbc160 returns for Value, after calling the method at
// 0x10d9d3c0 of its member at offset 0x2c with Value. The function, class, method and member names
// are invented; the offset and the bytes are the binary's.

class UnkType_10dbc1c0_Member
{
public:
    void Unk_10d9d3c0(int Value);
};

class UnkType_10dbc1c0_Item
{
public:
    unsigned char unk_0[0x2c];
    UnkType_10dbc1c0_Member unk_2c;
};

UnkType_10dbc1c0_Item* Unk_10dbc160(int Value);

// Unk_10dbc1c0
UnkType_10dbc1c0_Item* Unk_10dbc1c0(int Value)
{
    UnkType_10dbc1c0_Item* Item = Unk_10dbc160(Value);

    Item->unk_2c.Unk_10d9d3c0(Value);
    return Item;
}
