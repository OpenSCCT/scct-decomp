// campaign_leaf_33c740.cpp -- a member function at VA 0x10c3c740 that calls the member at VA
// 0x10bef850 and then, when the pointer at 0x40c is not null, clears the byte at 0x400 of its
// object. The class, method and member names are invented; the offsets and addresses are the
// binary's.

class UnkType_10c3c740_Item
{
public:
    unsigned char unk_000[0x400];
    unsigned char unk_400;
};

class UnkType_10c3c740
{
public:
    void Unk_10bef850();
    void Unk_10c3c740();

private:
    unsigned char unk_000[0x40c];
    UnkType_10c3c740_Item* unk_40c;
};

// UnkType_10c3c740::Unk_10c3c740
void UnkType_10c3c740::Unk_10c3c740()
{
    Unk_10bef850();
    if ( unk_40c )
    {
        unk_40c->unk_400 = 0;
    }
}
