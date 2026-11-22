// campaign_leaf_1b7680.cpp -- one function at file offset 0x1b7680, preferred VA 0x10ab7680. The
// assignment operator of a 4x4 float matrix: it copies the four rows of its argument and returns
// its object. The class, method and member names are invented; the offset and the bytes are the
// binary's.

struct UnkType_10ab7680_Plane
{
    float X;
    float Y;
    float Z;
    float W;

    UnkType_10ab7680_Plane& operator=(const UnkType_10ab7680_Plane& Other)
    {
        X = Other.X;
        Y = Other.Y;
        Z = Other.Z;
        W = Other.W;
        return *this;
    }
};

class UnkType_10ab7680
{
public:
    UnkType_10ab7680_Plane XPlane;
    UnkType_10ab7680_Plane YPlane;
    UnkType_10ab7680_Plane ZPlane;
    UnkType_10ab7680_Plane WPlane;

    UnkType_10ab7680& operator=(const UnkType_10ab7680& Other);
};

// UnkType_10ab7680::operator=
UnkType_10ab7680& UnkType_10ab7680::operator=(const UnkType_10ab7680& Other)
{
    XPlane = Other.XPlane;
    YPlane = Other.YPlane;
    ZPlane = Other.ZPlane;
    WPlane = Other.WPlane;
    return *this;
}
