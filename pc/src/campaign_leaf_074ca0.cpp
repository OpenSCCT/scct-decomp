// campaign_leaf_074ca0.cpp -- one function at file offset 0x74ca0, preferred VA 0x10974ca0. It
// adds the four floats of its argument to those of its object and returns a copy of the result by
// value. The class, method and member names are invented; the offset and the bytes are the
// binary's.

struct UnkVector
{
    float X;
    float Y;
    float Z;
};

struct UnkPlane : public UnkVector
{
    float W;

    UnkPlane(const UnkPlane& Other)
        : UnkVector(Other), W(Other.W)
    {
    }

    UnkPlane Unk_10974ca0(const UnkPlane& Other);
};

// UnkPlane::Unk_10974ca0
UnkPlane UnkPlane::Unk_10974ca0(const UnkPlane& Other)
{
    X += Other.X;
    Y += Other.Y;
    Z += Other.Z;
    W += Other.W;
    return *this;
}
