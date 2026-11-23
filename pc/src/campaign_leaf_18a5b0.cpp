// campaign_leaf_18a5b0.cpp -- free function at VA 0x10a8a5b0: picks vectors of three values 2r-1,
// with r from the free function at VA 0x10ccac40, until one lies inside the unit sphere, and
// returns it normalised by the method at VA 0x109b5e90 (a random unit vector). The class, member
// and function names are invented; the constants and the addresses are the binary's.

float Unk_10ccac40();

class UnkType_10a8a5b0
{
public:
    UnkType_10a8a5b0()
    {
    }
    UnkType_10a8a5b0(float X, float Y, float Z) : unk_0(X), unk_4(Y), unk_8(Z)
    {
    }

    UnkType_10a8a5b0 Unk_109b5e90() const;

    float unk_0;
    float unk_4;
    float unk_8;
};

// Unk_10a8a5b0
UnkType_10a8a5b0 Unk_10a8a5b0()
{
    UnkType_10a8a5b0 Result;

    do
    {
        Result.unk_0 = Unk_10ccac40() * 2.0f - 1.0f;
        Result.unk_4 = Unk_10ccac40() * 2.0f - 1.0f;
        Result.unk_8 = Unk_10ccac40() * 2.0f - 1.0f;
    } while ( Result.unk_0 * Result.unk_0 + Result.unk_4 * Result.unk_4
        + Result.unk_8 * Result.unk_8 > 1.0f );
    return Result.Unk_109b5e90();
}
