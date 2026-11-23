// campaign_leaf_05a990.cpp -- method at VA 0x1095a990: when the squared length of the three floats
// at 0x00-0x08 is at least 1e-8, scales them by its argument divided by the square root the free
// function at VA 0x10ccabc0 returns; returns this object. The class, member and function names
// are invented; the offsets, the constant and the address are the binary's.

double Unk_10ccabc0(double Value);

class UnkType_1095a990
{
public:
    UnkType_1095a990& Unk_1095a990(float Length);

private:
    float X;
    float Y;
    float Z;
};

// UnkType_1095a990::Unk_1095a990
UnkType_1095a990& UnkType_1095a990::Unk_1095a990(float Length)
{
    float SquareSum = X * X + Y * Y + Z * Z;
    if ( SquareSum >= 1e-8 )
    {
        float Scale = Length / Unk_10ccabc0(SquareSum);
        X *= Scale;
        Y *= Scale;
        Z *= Scale;
    }
    return *this;
}
