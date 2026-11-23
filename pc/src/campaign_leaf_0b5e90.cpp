// campaign_leaf_0b5e90.cpp -- method at VA 0x109b5e90 returning a 12-byte vector: divides 1.0 by
// the result of the function at VA 0x10ccabc0 called with the sum of the squares of the three
// floats at 0x00, and returns the three floats scaled by that. guess: a vector normalisation. The
// class, structure and method names are invented; the offsets and the address are the binary's.

double Unk_10ccabc0(double Value);

class UnkType_109b5e90
{
public:
    UnkType_109b5e90(float InX, float InY, float InZ) : unk_00(InX), unk_04(InY), unk_08(InZ)
    {
    }

    UnkType_109b5e90 Unk_109b5e90() const;

private:
    float unk_00;
    float unk_04;
    float unk_08;
};

// UnkType_109b5e90::Unk_109b5e90
UnkType_109b5e90 UnkType_109b5e90::Unk_109b5e90() const
{
    float Scale = 1.0 / Unk_10ccabc0(unk_00 * unk_00 + unk_04 * unk_04 + unk_08 * unk_08);
    return UnkType_109b5e90(unk_00 * Scale, unk_04 * Scale, unk_08 * Scale);
}
