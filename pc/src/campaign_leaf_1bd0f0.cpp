// campaign_leaf_1bd0f0.cpp -- one function at file offset 0x1bd0f0, preferred VA 0x10abd0f0. It
// scales the four floats of its object by its argument and returns a copy of the result by value.
// The class, method and member names are invented; the offset and the bytes are the binary's.

struct UnkType_10abd0f0_Vector
{
    float X;
    float Y;
    float Z;
};

struct UnkType_10abd0f0_Plane : public UnkType_10abd0f0_Vector
{
    float W;

    UnkType_10abd0f0_Plane(const UnkType_10abd0f0_Plane& Other)
        : UnkType_10abd0f0_Vector(Other), W(Other.W)
    {
    }

    UnkType_10abd0f0_Plane Unk_10abd0f0(float Scale);
};

// UnkType_10abd0f0_Plane::Unk_10abd0f0
UnkType_10abd0f0_Plane UnkType_10abd0f0_Plane::Unk_10abd0f0(float Scale)
{
    X *= Scale;
    Y *= Scale;
    Z *= Scale;
    W *= Scale;
    return *this;
}
