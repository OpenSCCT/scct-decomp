// campaign_leaf_33bb90.cpp -- a member function at VA 0x10c3bb90 that calls the member at VA
// 0x10bf0380 and then clears bit 9 (0x200) of the flags at 0x30. The class, method and member
// names are invented; the offsets and addresses are the binary's.

class UnkType_10c3bb90
{
public:
    void Unk_10bf0380();
    void Unk_10c3bb90();

private:
    unsigned char unk_00[0x30];
    unsigned int unk_30;
};

// UnkType_10c3bb90::Unk_10c3bb90
void UnkType_10c3bb90::Unk_10c3bb90()
{
    Unk_10bf0380();
    unk_30 &= ~0x200;
}
