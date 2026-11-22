// campaign_leaf_09fbd0.cpp -- one function at file offset 0x9fbd0, preferred VA 0x1099fbd0. A
// constructor: it copies its 12-byte argument to offset 0 and sets the three float triples that
// follow to (1, 0, 0), (0, 1, 0) and (0, 0, 1). The class, method and member names are invented;
// the offset and the bytes are the binary's.

struct UnkType_1099fbd0_Vector
{
    float X;
    float Y;
    float Z;

    UnkType_1099fbd0_Vector(float InX, float InY, float InZ)
        : X(InX), Y(InY), Z(InZ)
    {
    }
};

class UnkType_1099fbd0
{
public:
    UnkType_1099fbd0_Vector unk_0;
    UnkType_1099fbd0_Vector unk_c;
    UnkType_1099fbd0_Vector unk_18;
    UnkType_1099fbd0_Vector unk_24;

    UnkType_1099fbd0(const UnkType_1099fbd0_Vector& First);
};

// UnkType_1099fbd0::UnkType_1099fbd0
UnkType_1099fbd0::UnkType_1099fbd0(const UnkType_1099fbd0_Vector& First)
    : unk_0(First), unk_c(1, 0, 0), unk_18(0, 1, 0), unk_24(0, 0, 1)
{
}
