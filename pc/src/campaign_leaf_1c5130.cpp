// campaign_leaf_1c5130.cpp -- thiscall method at VA 0x10ac5130. When the object at 0x2e4 is set,
// lacks bit 8 of its flags at 0x300 and has bit 1 of its flags at 0x28, it passes the offset from
// this object's position at 0xe8 to that object's, the object and 0 to the method at VA 0x109b1920
// and returns 1 when that does; otherwise 0. The class, method and member names are invented.

class UnkType_10ac5130_Vector
{
public:
    // UnkType_10ac5130_Vector::UnkType_10ac5130_Vector
    UnkType_10ac5130_Vector(float InX, float InY, float InZ)
        : X(InX), Y(InY), Z(InZ)
    {
    }

    // UnkType_10ac5130_Vector::operator-
    UnkType_10ac5130_Vector operator-(const UnkType_10ac5130_Vector& Other) const
    {
        return UnkType_10ac5130_Vector(X - Other.X, Y - Other.Y, Z - Other.Z);
    }

    float X;
    float Y;
    float Z;
};

class UnkType_10ac5130
{
public:
    int Unk_10ac5130();
    int Unk_109b1920(UnkType_10ac5130_Vector Offset, UnkType_10ac5130* Other, int Value);

private:
    char unk_000[0x28];
    int unk_028;
    char unk_02c[0xe8 - 0x2c];
    UnkType_10ac5130_Vector unk_0e8;
    char unk_0f4[0x2e4 - 0xf4];
    UnkType_10ac5130* unk_2e4;
    char unk_2e8[0x300 - 0x2e8];
    int unk_300;
};

// UnkType_10ac5130::Unk_10ac5130
int UnkType_10ac5130::Unk_10ac5130()
{
    UnkType_10ac5130* Other = unk_2e4;
    if ( Other && !(Other->unk_300 & 8) && (Other->unk_028 & 1) )
    {
        if ( Unk_109b1920(Other->unk_0e8 - unk_0e8, Other, 0) )
        {
            return 1;
        }
    }
    return 0;
}
