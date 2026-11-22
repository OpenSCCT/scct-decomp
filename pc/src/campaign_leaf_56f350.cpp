// campaign_leaf_56f350.cpp -- one function at file offset 0x56f350, preferred VA 0x10e6f350.
// It subtracts Other's four three-float vectors from the object's, component by component. The
// class, structure, method and member names are invented; the offset and the bytes are the
// binary's.

struct UnkType_10e6f350_Vector
{
    float X;
    float Y;
    float Z;

    void operator-=(const UnkType_10e6f350_Vector& V)
    {
        X -= V.X;
        Y -= V.Y;
        Z -= V.Z;
    }
};

class UnkType_10e6f350
{
public:
    UnkType_10e6f350_Vector unk_0;
    UnkType_10e6f350_Vector unk_c;
    UnkType_10e6f350_Vector unk_18;
    UnkType_10e6f350_Vector unk_24;

    void Unk_10e6f350(const UnkType_10e6f350& Other);
};

// UnkType_10e6f350::Unk_10e6f350
void UnkType_10e6f350::Unk_10e6f350(const UnkType_10e6f350& Other)
{
    unk_0 -= Other.unk_0;
    unk_c -= Other.unk_c;
    unk_18 -= Other.unk_18;
    unk_24 -= Other.unk_24;
}
