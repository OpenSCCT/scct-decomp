// campaign_leaf_3647d0.cpp -- a member function at VA 0x10c647d0 that calls the member at VA
// 0x1099db70 and then, when the pointer at 0x6c is not null and bit 15 of the flags at 0x2c of its
// object is set, copies the pointer to 0x2e4. The class, method and member names are invented; the
// offsets and addresses are the binary's.

class UnkType_10c647d0_Item
{
public:
    unsigned char unk_00[0x2c];
    unsigned int unk_2c;
};

class UnkType_10c647d0
{
public:
    void Unk_1099db70();
    void Unk_10c647d0();

private:
    unsigned char unk_000[0x6c];
    UnkType_10c647d0_Item* unk_06c;
    unsigned char unk_070[0x2e4 - 0x70];
    UnkType_10c647d0_Item* unk_2e4;
};

// UnkType_10c647d0::Unk_10c647d0
void UnkType_10c647d0::Unk_10c647d0()
{
    Unk_1099db70();
    if ( unk_06c && ( unk_06c->unk_2c & 0x8000 ) )
    {
        unk_2e4 = unk_06c;
    }
}
