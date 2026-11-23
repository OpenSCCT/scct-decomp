// campaign_leaf_46c6b0.cpp -- method at VA 0x10d6c6b0: stores 65536 over Rate, truncated, at 0xec
// (a 16.16 fixed-point value) and returns the reciprocal of the value it replaced. The class,
// member, method and parameter names are invented; the offset and the constants are the
// binary's.

class UnkType_10d6c6b0
{
public:
    float Unk_10d6c6b0(float Rate);

private:
    char unk_0[0xec];
    int unk_ec;
};

// UnkType_10d6c6b0::Unk_10d6c6b0
float UnkType_10d6c6b0::Unk_10d6c6b0(float Rate)
{
    float Old = unk_ec / 65536.0f;
    float Inverse = 1.0f / Rate;

    unk_ec = (int)( Inverse * 65536.0f );
    return 1.0f / Old;
}
