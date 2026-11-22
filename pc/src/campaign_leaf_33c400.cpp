// campaign_leaf_33c400.cpp -- a member function at VA 0x10c3c400 that calls the member at VA
// 0x10bf0380 and then clears bit 0 of the flags at 0x5b4. The class, method and member names are
// invented; the offsets and addresses are the binary's.

class UnkType_10c3c400
{
public:
    void Unk_10bf0380();
    void Unk_10c3c400();

private:
    unsigned char unk_000[0x5b4];
    unsigned int unk_5b4;
};

// UnkType_10c3c400::Unk_10c3c400
void UnkType_10c3c400::Unk_10c3c400()
{
    Unk_10bf0380();
    unk_5b4 &= ~1;
}
