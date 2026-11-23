// campaign_leaf_1be080.cpp -- method at VA 0x10abe080: transforms the point Point, with W 1,
// through the method at VA 0x10943d00 of the object at 0x27c and returns the result divided by its
// W, keeping W. The class, member, method and parameter names are invented; the offset, the
// constant and the address are the binary's.

class UnkType_10abe080_Point
{
public:
    float unk_0;
    float unk_4;
    float unk_8;
};

class UnkType_10abe080_Plane
{
public:
    UnkType_10abe080_Plane()
    {
    }
    UnkType_10abe080_Plane(float X, float Y, float Z, float W)
        : unk_0(X), unk_4(Y), unk_8(Z), unk_c(W)
    {
    }

    float unk_0;
    float unk_4;
    float unk_8;
    float unk_c;
};

class UnkType_10abe080_Transform
{
public:
    UnkType_10abe080_Plane Unk_10943d00(const UnkType_10abe080_Plane& Plane);
};

class UnkType_10abe080
{
public:
    UnkType_10abe080_Plane Unk_10abe080(UnkType_10abe080_Point Point);

private:
    char unk_0[0x27c];
    UnkType_10abe080_Transform unk_27c;
};

// UnkType_10abe080::Unk_10abe080
UnkType_10abe080_Plane UnkType_10abe080::Unk_10abe080(UnkType_10abe080_Point Point)
{
    UnkType_10abe080_Plane Result
        = unk_27c.Unk_10943d00(UnkType_10abe080_Plane(Point.unk_0, Point.unk_4, Point.unk_8, 1.0f));
    float Scale = 1.0f / Result.unk_c;

    return UnkType_10abe080_Plane(Result.unk_0 * Scale, Result.unk_4 * Scale, Result.unk_8 * Scale,
        Result.unk_c);
}
