// campaign_leaf_1931d0.cpp -- exchanges the vectors at the two arguments. File offset 0x1931d0, VA
// 0x10a931d0. The class and method names are invented; the bytes show no this pointer and caller
// cleanup, and the vector type is a guess.

class UnkVec_10a931d0
{
public:
    int unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10a931d0
{
public:
    static void UnkStatic_10a931d0(UnkVec_10a931d0 *A, UnkVec_10a931d0 *B);
};

// UnkType_10a931d0::UnkStatic_10a931d0
void UnkType_10a931d0::UnkStatic_10a931d0(UnkVec_10a931d0 *A, UnkVec_10a931d0 *B)
{
    UnkVec_10a931d0 temp;

    temp = *A;
    *A = *B;
    *B = temp;
}
