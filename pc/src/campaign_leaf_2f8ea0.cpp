// campaign_leaf_2f8ea0.cpp -- a member function at VA 0x10bf8ea0 that calls the member at VA
// 0x10bf8d90 and then, when the pointer at 0x48c is not null, stores 0.5 in the float at 0x2b8 of
// its object. The class, method and member names are invented; the offsets, addresses and constant
// are the binary's.

class UnkType_10bf8ea0_Item
{
public:
    unsigned char unk_000[0x2b8];
    float unk_2b8;
};

class UnkType_10bf8ea0
{
public:
    void Unk_10bf8d90();
    void Unk_10bf8ea0();

private:
    unsigned char unk_000[0x48c];
    UnkType_10bf8ea0_Item* unk_48c;
};

// UnkType_10bf8ea0::Unk_10bf8ea0
void UnkType_10bf8ea0::Unk_10bf8ea0()
{
    Unk_10bf8d90();
    if ( unk_48c )
    {
        unk_48c->unk_2b8 = 0.5f;
    }
}
