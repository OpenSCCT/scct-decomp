// campaign_leaf_2f3cf0.cpp -- one function at file offset 0x2f3cf0, preferred VA 0x10bf3cf0. When
// the object reached through offsets 0x7c and 0x38 has a nonzero word at offset 0xa8 and a zero
// word at offset 0xa4, it stores the vector (115, -50, 20) through its first argument. Its second
// argument is never read. The class, method and member names are invented; the offset and the
// bytes are the binary's.

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

class UnkInner
{
public:
    unsigned char unk_0[0xa4];
    int unk_a4;
    int unk_a8;
};

class UnkOuter
{
public:
    unsigned char unk_0[0x38];
    UnkInner* unk_38;
};

class UnkType_10bf3cf0
{
public:
    unsigned char unk_0[0x7c];
    UnkOuter* unk_7c;

    void Unk_10bf3cf0(UnkVector& Out, int Unused);
};

// UnkType_10bf3cf0::Unk_10bf3cf0
void UnkType_10bf3cf0::Unk_10bf3cf0(UnkVector& Out, int Unused)
{
    UnkInner* Inner = unk_7c->unk_38;
    if ( Inner->unk_a8 && !Inner->unk_a4 )
    {
        Out = UnkVector(115.0f, -50.0f, 20.0f);
    }
}
