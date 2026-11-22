// campaign_leaf_11d4e0.cpp -- returns the squared distance between the two vectors given as its
// arguments. File offset 0x11d4e0, VA 0x10a1d4e0. The class and method names are invented; the
// vector type is a guess.

class UnkVec_11d4e0
{
public:
    float unk_00;
    float unk_04;
    float unk_08;
};

class UnkType_11d4e0
{
public:
    static float UnkStatic_11d4e0(UnkVec_11d4e0 *A, UnkVec_11d4e0 *B);
};

// UnkType_11d4e0::UnkStatic_11d4e0
float UnkType_11d4e0::UnkStatic_11d4e0(UnkVec_11d4e0 *A, UnkVec_11d4e0 *B)
{
    float dx;
    float dy;
    float dz;

    dx = B->unk_00 - A->unk_00;
    dy = B->unk_04 - A->unk_04;
    dz = B->unk_08 - A->unk_08;
    return dz * dz + dy * dy + dx * dx;
}
