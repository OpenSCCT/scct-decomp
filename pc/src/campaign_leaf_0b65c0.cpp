// campaign_leaf_0b65c0.cpp -- method at VA 0x109b65c0: returns whether the result of the method at
// VA 0x10a3c6b0 is less than the double at 0x48. The class, member and method names are invented;
// the offset and the address are the binary's.

class UnkType_109b65c0
{
public:
    int Unk_109b65c0();
    double Unk_10a3c6b0();

private:
    unsigned char unk_00[0x48];
    double unk_48;
};

// UnkType_109b65c0::Unk_109b65c0
int UnkType_109b65c0::Unk_109b65c0()
{
    return Unk_10a3c6b0() < unk_48;
}
