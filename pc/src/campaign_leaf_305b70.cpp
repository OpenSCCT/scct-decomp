// campaign_leaf_305b70.cpp -- a member function at VA 0x10c05b70: when bit 0 of the flags at 0x358
// is set, it calls the member at VA 0x10c05a50 with the argument 1. The class, method and member
// names are invented; the offsets and addresses are the binary's.

class UnkType_10c05b70
{
public:
    void Unk_10c05a50(int Value);
    void Unk_10c05b70();

private:
    unsigned char unk_000[0x358];
    unsigned int unk_358;
};

// UnkType_10c05b70::Unk_10c05b70
void UnkType_10c05b70::Unk_10c05b70()
{
    if ( unk_358 & 1 )
    {
        Unk_10c05a50(1);
    }
}
