// campaign_leaf_02d200.cpp -- method at VA 0x1092d200: returns the square root, from the free
// function at VA 0x10ccabc0, of the sum of the squares of the floats at 0x00 and 0x04. The class,
// member and function names are invented; the offsets and the address are the binary's.

double Unk_10ccabc0(double Value);

class UnkType_1092d200
{
public:
    float Unk_1092d200();

private:
    float X;
    float Y;
};

// UnkType_1092d200::Unk_1092d200
float UnkType_1092d200::Unk_1092d200()
{
    return Unk_10ccabc0(X * X + Y * Y);
}
