// campaign_leaf_33bb60.cpp -- a member function at VA 0x10c3bb60 that calls the member at VA
// 0x10bf1160, clears bit 9 (0x200) of the flags at 0x28 and sets it in the flags at 0x30. The
// class, method and member names are invented; the offsets and addresses are the binary's.

class UnkType_10c3bb60
{
public:
    void Unk_10bf1160();
    void Unk_10c3bb60();

private:
    unsigned char unk_00[0x28];
    unsigned int unk_28;
    int unk_2c;
    unsigned int unk_30;
};

// UnkType_10c3bb60::Unk_10c3bb60
void UnkType_10c3bb60::Unk_10c3bb60()
{
    Unk_10bf1160();
    unk_28 &= ~0x200;
    unk_30 |= 0x200;
}
