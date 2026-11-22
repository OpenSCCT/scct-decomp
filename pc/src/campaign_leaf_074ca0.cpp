// campaign_leaf_074ca0.cpp -- one function at file offset 0x74ca0, preferred VA 0x10974ca0. It
// adds the four floats of its argument to those of its object and returns a copy of the result by
// value. The class, method and member names are invented; the offset and the bytes are the
// binary's.

struct UnkType_10974ca0_Vector
{
    float X;
    float Y;
    float Z;
};

struct UnkType_10974ca0_Plane : public UnkType_10974ca0_Vector
{
    float W;

    UnkType_10974ca0_Plane(const UnkType_10974ca0_Plane& Other)
        : UnkType_10974ca0_Vector(Other), W(Other.W)
    {
    }

    UnkType_10974ca0_Plane Unk_10974ca0(const UnkType_10974ca0_Plane& Other);
};

// UnkType_10974ca0_Plane::Unk_10974ca0
UnkType_10974ca0_Plane UnkType_10974ca0_Plane::Unk_10974ca0(const UnkType_10974ca0_Plane& Other)
{
    X += Other.X;
    Y += Other.Y;
    Z += Other.Z;
    W += Other.W;
    return *this;
}
