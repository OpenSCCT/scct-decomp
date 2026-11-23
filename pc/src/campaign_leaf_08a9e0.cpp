// campaign_leaf_08a9e0.cpp -- free function at VA 0x1098a9e0: stores in Result the transpose of
// the 3x3 rotation part of the 4x4 matrix Source, a zero last column with 1 in its corner, and
// Source's translation row times Scale. The class, member, function and parameter names are
// invented; the offsets are the binary's.

class UnkType_1098a9e0
{
public:
    float M[4][4];
};

// Unk_1098a9e0
void Unk_1098a9e0(const UnkType_1098a9e0& Source, float Scale, UnkType_1098a9e0& Result)
{
    Result.M[0][0] = Source.M[0][0];
    Result.M[1][0] = Source.M[0][1];
    Result.M[2][0] = Source.M[0][2];
    Result.M[0][1] = Source.M[1][0];
    Result.M[1][1] = Source.M[1][1];
    Result.M[2][1] = Source.M[1][2];
    Result.M[0][2] = Source.M[2][0];
    Result.M[1][2] = Source.M[2][1];
    Result.M[2][2] = Source.M[2][2];
    Result.M[0][3] = 0.0f;
    Result.M[1][3] = 0.0f;
    Result.M[2][3] = 0.0f;
    Result.M[3][3] = 1.0f;
    Result.M[3][0] = Scale * Source.M[3][0];
    Result.M[3][1] = Scale * Source.M[3][1];
    Result.M[3][2] = Scale * Source.M[3][2];
}
