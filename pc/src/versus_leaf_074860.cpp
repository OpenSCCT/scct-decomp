// versus_leaf_074860.cpp -- one function at file offset 0x74860, preferred VA 0x10974860.
// It compares the 4x4 float matrix at ECX with the matrix at EAX, element by element, and returns
// 1 when all sixteen floats are equal and 0 otherwise. The link chooses the register convention
// from the callers. The matrix type and the function name are invented; the layout is the
// binary's (rows of four floats, 0x10 bytes apart).

struct UnkType_74860_Matrix
{
    float M[4][4];

    int Unk_74860(const UnkType_74860_Matrix *Other);
};

/*
================
UnkType_74860_Matrix::Unk_74860

Returns 1 when every element of this matrix equals the matching element of Other, else 0.
================
*/
__declspec(noinline) int UnkType_74860_Matrix::Unk_74860(const UnkType_74860_Matrix *Other)
{
    int Row;
    int Column;

    for (Row = 0; Row < 4; Row++)
    {
        for (Column = 0; Column < 4; Column++)
        {
            if (M[Row][Column] != Other->M[Row][Column])
                return 0;
        }
    }
    return 1;
}

// Scaffolding for the link, not part of the unit.
int Driver_74860(UnkType_74860_Matrix *This, const UnkType_74860_Matrix *Other)
{
    return This->Unk_74860(Other);
}
