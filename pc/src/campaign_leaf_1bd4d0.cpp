// campaign_leaf_1bd4d0.cpp -- method at VA 0x10abd4d0: transforms the point Point, with W 1,
// through the method at VA 0x10943d00 of the object at 0x10c and returns the result divided by its
// W, keeping W. The class, member, method and parameter names are invented; the offset, the
// constant and the address are the binary's.

class UnkType_10abd4d0_Point
{
public:
    float unk_0;
    float unk_4;
    float unk_8;
};

class UnkType_10abd4d0_Plane
{
public:
    UnkType_10abd4d0_Plane()
    {
    }
    UnkType_10abd4d0_Plane(float X, float Y, float Z, float W)
        : unk_0(X), unk_4(Y), unk_8(Z), unk_c(W)
    {
    }

    float unk_0;
    float unk_4;
    float unk_8;
    float unk_c;
};

class UnkType_10abd4d0_Transform
{
public:
    UnkType_10abd4d0_Plane Unk_10943d00(const UnkType_10abd4d0_Plane& Plane);
};

class UnkType_10abd4d0
{
public:
    UnkType_10abd4d0_Plane Unk_10abd4d0(UnkType_10abd4d0_Point Point);

private:
    char unk_0[0x10c];
    UnkType_10abd4d0_Transform unk_10c;
};

// UnkType_10abd4d0::Unk_10abd4d0
UnkType_10abd4d0_Plane UnkType_10abd4d0::Unk_10abd4d0(UnkType_10abd4d0_Point Point)
{
    UnkType_10abd4d0_Plane Result
        = unk_10c.Unk_10943d00(UnkType_10abd4d0_Plane(Point.unk_0, Point.unk_4, Point.unk_8, 1.0f));
    float Scale = 1.0f / Result.unk_c;

    return UnkType_10abd4d0_Plane(Result.unk_0 * Scale, Result.unk_4 * Scale, Result.unk_8 * Scale,
        Result.unk_c);
}
