// campaign_leaf_1bd0f0.cpp -- one function at file offset 0x1bd0f0, preferred VA 0x10abd0f0. It
// scales the four floats of its object by its argument and returns a copy of the result by value.
// The class, method and member names are invented; the offset and the bytes are the binary's.

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

    UnkPlane Unk_10abd0f0(float Scale);
};

// UnkPlane::Unk_10abd0f0
UnkPlane UnkPlane::Unk_10abd0f0(float Scale)
{
    X *= Scale;
    Y *= Scale;
    Z *= Scale;
    W *= Scale;
    return *this;
}
