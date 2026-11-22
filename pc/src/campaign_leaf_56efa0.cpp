// campaign_leaf_56efa0.cpp -- one function at file offset 0x56efa0, preferred VA 0x10e6efa0.
// It sets the object's three rows of four floats to the transpose of the 3x3 part of Other and
// zeroes the fourth column. The class, method and member names are invented; the offset and the
// bytes are the binary's.

class UnkType_10e6efa0
{
public:
    float M[3][4];

    void Unk_10e6efa0(const UnkType_10e6efa0& Other);
};

// UnkType_10e6efa0::Unk_10e6efa0
void UnkType_10e6efa0::Unk_10e6efa0(const UnkType_10e6efa0& Other)
{
    M[0][0] = Other.M[0][0];
    M[1][1] = Other.M[1][1];
    M[2][2] = Other.M[2][2];
    M[0][3] = 0.0f;
    M[1][3] = 0.0f;
    M[2][3] = 0.0f;
    M[0][1] = Other.M[1][0];
    M[1][0] = Other.M[0][1];
    M[0][2] = Other.M[2][0];
    M[2][0] = Other.M[0][2];
    M[1][2] = Other.M[2][1];
    M[2][1] = Other.M[1][2];
}
