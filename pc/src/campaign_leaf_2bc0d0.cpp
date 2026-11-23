// campaign_leaf_2bc0d0.cpp -- method at VA 0x10bbc0d0: returns the square root, from the free
// function at VA 0x10ccabc0, of the sum of the squares of the floats at 0x3b0 and 0x3b4. The
// class, member and function names are invented; the offsets and the address are the binary's.

double Unk_10ccabc0(double Value);

class UnkType_10bbc0d0
{
public:
    float Unk_10bbc0d0();

private:
    char unk_0[0x3b0];
    float unk_3b0;
    float unk_3b4;
};

// UnkType_10bbc0d0::Unk_10bbc0d0
float UnkType_10bbc0d0::Unk_10bbc0d0()
{
    return Unk_10ccabc0(unk_3b0 * unk_3b0 + unk_3b4 * unk_3b4);
}
