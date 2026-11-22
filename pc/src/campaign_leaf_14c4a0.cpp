// campaign_leaf_14c4a0.cpp -- one function at file offset 0x14c4a0, preferred VA 0x10a4c4a0. It
// returns by value a copy of the four floats at offset 0x44 of its object, and pops one more
// argument it never reads. The class, method and member names are invented; the offset and the
// bytes are the binary's.

struct UnkType_10a4c4a0_Vector
{
    float X;
    float Y;
    float Z;
};

struct UnkType_10a4c4a0_Plane : public UnkType_10a4c4a0_Vector
{
    float W;

    UnkType_10a4c4a0_Plane(const UnkType_10a4c4a0_Plane& Other)
        : UnkType_10a4c4a0_Vector(Other), W(Other.W)
    {
    }
};

class UnkType_10a4c4a0
{
public:
    unsigned char unk_0[0x44];
    UnkType_10a4c4a0_Plane unk_44;

    UnkType_10a4c4a0_Plane Unk_10a4c4a0(int Unused) const;
};

// UnkType_10a4c4a0::Unk_10a4c4a0
UnkType_10a4c4a0_Plane UnkType_10a4c4a0::Unk_10a4c4a0(int Unused) const
{
    return unk_44;
}
