// campaign_leaf_02d230.cpp -- method at VA 0x1092d230: when the squared length of the three floats
// at 0x00-0x08 is at least 1e-8, scales them by the reciprocal of the square root the free
// function at VA 0x10ccabc0 returns and returns 1; otherwise returns 0. The class, member and
// function names are invented; the offsets, the constants and the address are the binary's.

double Unk_10ccabc0(double Value);

class UnkType_1092d230
{
public:
    int Unk_1092d230();

private:
    float X;
    float Y;
    float Z;
};

// UnkType_1092d230::Unk_1092d230
int UnkType_1092d230::Unk_1092d230()
{
    float SquareSum = X * X + Y * Y + Z * Z;
    if ( SquareSum >= 1e-8 )
    {
        float Scale = 1.0 / Unk_10ccabc0(SquareSum);
        X *= Scale;
        Y *= Scale;
        Z *= Scale;
        return 1;
    }
    return 0;
}
