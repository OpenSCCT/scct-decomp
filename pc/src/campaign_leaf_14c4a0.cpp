// campaign_leaf_14c4a0.cpp -- one function at file offset 0x14c4a0, preferred VA 0x10a4c4a0. It
// returns by value a copy of the four floats at offset 0x44 of its object, and pops one more
// argument it never reads. The class, method and member names are invented; the offset and the
// bytes are the binary's.

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
};

class UnkType_10a4c4a0
{
public:
    unsigned char unk_0[0x44];
    UnkPlane unk_44;

    UnkPlane GetUnk44(int Unused) const;
};

// UnkType_10a4c4a0::GetUnk44
UnkPlane UnkType_10a4c4a0::GetUnk44(int Unused) const
{
    return unk_44;
}
