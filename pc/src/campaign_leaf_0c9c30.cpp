// campaign_leaf_0c9c30.cpp -- one function at file offset 0xc9c30, preferred VA 0x109c9c30. When
// the object at offset 0x288 exists it adds the vector its argument refers to to both vectors of
// that object at offsets 0xa8 and 0xd8. The class, method and member names are invented; the
// offset and the bytes are the binary's.

struct UnkType_109c9c30_Vector
{
    float X;
    float Y;
    float Z;

    UnkType_109c9c30_Vector& operator+=(const UnkType_109c9c30_Vector& Other)
    {
        X += Other.X;
        Y += Other.Y;
        Z += Other.Z;
        return *this;
    }
};

class UnkType_109c9c30_Owner
{
public:
    unsigned char unk_0[0xa8];
    UnkType_109c9c30_Vector unk_a8;
    unsigned char unk_b4[0xd8 - 0xb4];
    UnkType_109c9c30_Vector unk_d8;
};

class UnkType_109c9c30
{
public:
    unsigned char unk_0[0x288];
    UnkType_109c9c30_Owner* unk_288;

    void Unk_109c9c30(const UnkType_109c9c30_Vector& Delta);
};

// UnkType_109c9c30::Unk_109c9c30
void UnkType_109c9c30::Unk_109c9c30(const UnkType_109c9c30_Vector& Delta)
{
    if ( unk_288 )
    {
        unk_288->unk_a8 += Delta;
        unk_288->unk_d8 += Delta;
    }
}
