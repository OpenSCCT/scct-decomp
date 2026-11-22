// campaign_leaf_0cab60.cpp -- one function at file offset 0xcab60, preferred VA 0x109cab60. A copy
// constructor: it copies the four float triples of its argument into the new object. The class
// and member names are invented; the offset and the bytes are the binary's.

struct UnkType_109cab60_Vector
{
    float X;
    float Y;
    float Z;

    UnkType_109cab60_Vector(const UnkType_109cab60_Vector& Other)
        : X(Other.X), Y(Other.Y), Z(Other.Z)
    {
    }
};

class UnkType_109cab60
{
public:
    UnkType_109cab60_Vector unk_0;
    UnkType_109cab60_Vector unk_c;
    UnkType_109cab60_Vector unk_18;
    UnkType_109cab60_Vector unk_24;

    UnkType_109cab60(const UnkType_109cab60& Other);
};

// UnkType_109cab60::UnkType_109cab60
UnkType_109cab60::UnkType_109cab60(const UnkType_109cab60& Other)
    : unk_0(Other.unk_0), unk_c(Other.unk_c), unk_18(Other.unk_18), unk_24(Other.unk_24)
{
}
