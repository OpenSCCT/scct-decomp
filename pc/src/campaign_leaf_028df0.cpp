// campaign_leaf_028df0.cpp -- method at VA 0x10928df0: returns the square root, from the free
// function at VA 0x10ccabc0, of the sum of the squares of the floats at 0x00, 0x04 and 0x08. The
// class, member and function names are invented; the offsets and the address are the binary's.

double Unk_10ccabc0(double Value);

class UnkType_10928df0
{
public:
    float Unk_10928df0();

private:
    float X;
    float Y;
    float Z;
};

// UnkType_10928df0::Unk_10928df0
float UnkType_10928df0::Unk_10928df0()
{
    return Unk_10ccabc0(X * X + Y * Y + Z * Z);
}
