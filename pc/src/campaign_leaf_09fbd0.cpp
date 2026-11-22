// campaign_leaf_09fbd0.cpp -- one function at file offset 0x9fbd0, preferred VA 0x1099fbd0. A
// constructor: it copies its 12-byte argument to offset 0 and sets the three float triples that
// follow to (1, 0, 0), (0, 1, 0) and (0, 0, 1). The class, method and member names are invented;
// the offset and the bytes are the binary's.

struct UnkVector
{
    float X;
    float Y;
    float Z;

    UnkVector(float InX, float InY, float InZ)
        : X(InX), Y(InY), Z(InZ)
    {
    }
};

class UnkType_1099fbd0
{
public:
    UnkVector unk_0;
    UnkVector unk_c;
    UnkVector unk_18;
    UnkVector unk_24;

    UnkType_1099fbd0(const UnkVector& First);
};

// UnkType_1099fbd0::UnkType_1099fbd0
UnkType_1099fbd0::UnkType_1099fbd0(const UnkVector& First)
    : unk_0(First), unk_c(1, 0, 0), unk_18(0, 1, 0), unk_24(0, 0, 1)
{
}
