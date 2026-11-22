// campaign_leaf_311c00.cpp -- a member function at VA 0x10c11c00 that stores the result of the
// member at VA 0x10a3c6b0 plus 15 in the double at 0x50, and that sum plus 2 in the double at 0x48.
// The class, method and member names are invented; the offsets, addresses and constants are the
// binary's.

class UnkType_10c11c00
{
public:
    double Unk_10a3c6b0();
    void Unk_10c11c00();

private:
    unsigned char unk_00[0x48];
    double unk_48;
    double unk_50;
};

// UnkType_10c11c00::Unk_10c11c00
void UnkType_10c11c00::Unk_10c11c00()
{
    unk_50 = Unk_10a3c6b0() + 15.0;
    unk_48 = unk_50 + 2.0;
}
