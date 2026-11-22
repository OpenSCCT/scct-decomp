// campaign_leaf_211930.cpp -- one function at file offset 0x211930, preferred VA 0x10b11930. It
// fills its first argument, a 4x4 float matrix, from its second, an origin followed by three axes:
// the axes become the matrix's first three columns, the origin its last row, with 0 in the last
// column and 1 in its corner. Its this pointer is never read. The class, method and member names
// are invented; the offset and the bytes are the binary's.

struct UnkType_10b11930_Vector
{
    float X;
    float Y;
    float Z;
};

struct UnkType_10b11930_Coords
{
    UnkType_10b11930_Vector Origin;
    UnkType_10b11930_Vector XAxis;
    UnkType_10b11930_Vector YAxis;
    UnkType_10b11930_Vector ZAxis;
};

struct UnkType_10b11930_Matrix
{
    float M[4][4];
};

class UnkType_10b11930
{
public:
    void Unk_10b11930(UnkType_10b11930_Matrix& Out, const UnkType_10b11930_Coords& Coords);
};

// UnkType_10b11930::Unk_10b11930
void UnkType_10b11930::Unk_10b11930(UnkType_10b11930_Matrix& Out,
    const UnkType_10b11930_Coords& Coords)
{
    Out.M[0][0] = Coords.XAxis.X;
    Out.M[1][0] = Coords.XAxis.Y;
    Out.M[2][0] = Coords.XAxis.Z;
    Out.M[0][1] = Coords.YAxis.X;
    Out.M[1][1] = Coords.YAxis.Y;
    Out.M[2][1] = Coords.YAxis.Z;
    Out.M[0][2] = Coords.ZAxis.X;
    Out.M[1][2] = Coords.ZAxis.Y;
    Out.M[2][2] = Coords.ZAxis.Z;
    Out.M[3][0] = Coords.Origin.X;
    Out.M[3][1] = Coords.Origin.Y;
    Out.M[3][2] = Coords.Origin.Z;
    Out.M[0][3] = 0.0f;
    Out.M[1][3] = 0.0f;
    Out.M[2][3] = 0.0f;
    Out.M[3][3] = 1.0f;
}
