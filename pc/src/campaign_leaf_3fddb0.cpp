// campaign_leaf_3fddb0.cpp -- one function at file offset 0x3fddb0, preferred VA 0x10cfddb0. It
// fills Count + Degree + 1 words of the array's data: 0 below Degree, then rising by one from 1
// up to index Count, then Count - Degree + 2. It never reads its this pointer. The class,
// method, structure, member and parameter names are invented; the offsets and the bytes are the
// binary's.

struct UnkType_10cfddb0_Array
{
    int* unk_0;
};

class UnkType_10cfddb0
{
public:
    void Unk_10cfddb0(UnkType_10cfddb0_Array& Out, int Count, int Degree) const;
};

// UnkType_10cfddb0::Unk_10cfddb0
// guess: a clamped B-spline knot vector.
void UnkType_10cfddb0::Unk_10cfddb0(UnkType_10cfddb0_Array& Out, int Count, int Degree) const
{
    int Index;

    for ( Index = 0; Index <= Count + Degree; Index++ )
    {
        if ( Index < Degree )
        {
            Out.unk_0[Index] = 0;
        }
        else if ( Index <= Count )
        {
            Out.unk_0[Index] = Index - Degree + 1;
        }
        else
        {
            Out.unk_0[Index] = Count - Degree + 2;
        }
    }
}
