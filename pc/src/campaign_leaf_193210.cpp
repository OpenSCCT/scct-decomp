// campaign_leaf_193210.cpp -- exchanges the vectors at the two arguments. File offset 0x193210, VA
// 0x10a93210. The class and method names are invented; the bytes show no this pointer and caller
// cleanup, and the vector type is a guess.

class UnkVec_10a93210
{
public:
    int unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10a93210
{
public:
    static void UnkStatic_10a93210(UnkVec_10a93210 *A, UnkVec_10a93210 *B);
};

// UnkType_10a93210::UnkStatic_10a93210
void UnkType_10a93210::UnkStatic_10a93210(UnkVec_10a93210 *A, UnkVec_10a93210 *B)
{
    UnkVec_10a93210 temp;

    temp = *A;
    *A = *B;
    *B = temp;
}
