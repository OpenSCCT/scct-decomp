// campaign_leaf_56f3c0.cpp -- one function at file offset 0x56f3c0, preferred VA 0x10e6f3c0.
// It multiplies the object's four three-float vectors by Scale. The class, structure, method and
// member names are invented; the offset and the bytes are the binary's.

struct UnkType_10e6f3c0_Vector
{
    float X;
    float Y;
    float Z;

    void operator*=(float Scale)
    {
        X *= Scale;
        Y *= Scale;
        Z *= Scale;
    }
};

class UnkType_10e6f3c0
{
public:
    UnkType_10e6f3c0_Vector unk_0;
    UnkType_10e6f3c0_Vector unk_c;
    UnkType_10e6f3c0_Vector unk_18;
    UnkType_10e6f3c0_Vector unk_24;

    void Unk_10e6f3c0(float Scale);
};

// UnkType_10e6f3c0::Unk_10e6f3c0
void UnkType_10e6f3c0::Unk_10e6f3c0(float Scale)
{
    unk_0 *= Scale;
    unk_c *= Scale;
    unk_18 *= Scale;
    unk_24 *= Scale;
}
