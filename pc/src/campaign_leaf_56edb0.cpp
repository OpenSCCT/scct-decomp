// campaign_leaf_56edb0.cpp -- one function at file offset 0x56edb0, preferred VA 0x10e6edb0.
// It subtracts the fourth row of the 4x4 matrix M from V and sets the object's three floats to the
// dot products of the difference with the first three rows (the inverse of a rigid transform).
// The class, structure, method and member names are invented; the offset and the bytes are the
// binary's.

struct UnkType_10e6edb0_Matrix
{
    float M[4][4];
};

struct UnkType_10e6edb0_Vector
{
    float X;
    float Y;
    float Z;
};

class UnkType_10e6edb0
{
public:
    float X;
    float Y;
    float Z;

    void Unk_10e6edb0(const UnkType_10e6edb0_Matrix& M, const UnkType_10e6edb0_Vector& V);
};

// UnkType_10e6edb0::Unk_10e6edb0
void UnkType_10e6edb0::Unk_10e6edb0(const UnkType_10e6edb0_Matrix& M,
                                    const UnkType_10e6edb0_Vector& V)
{
    float DX = V.X - M.M[3][0];
    float DY = V.Y - M.M[3][1];
    float DZ = V.Z - M.M[3][2];

    X = DX * M.M[0][0] + DY * M.M[0][1] + DZ * M.M[0][2];
    Y = DX * M.M[1][0] + DY * M.M[1][1] + DZ * M.M[1][2];
    Z = DX * M.M[2][0] + DY * M.M[2][1] + DZ * M.M[2][2];
}
