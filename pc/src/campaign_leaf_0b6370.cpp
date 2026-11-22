// campaign_leaf_0b6370.cpp -- one function at file offset 0xb6370, preferred VA 0x109b6370. It
// returns 1 when the point its first argument points to lies inside the box (minimum then maximum
// corner) its second argument points to, bounds included; otherwise 0. It has no this pointer. The
// class, method and member names are invented; the offset and the bytes are the binary's.

struct UnkType_109b6370_Vector
{
    float X;
    float Y;
    float Z;
};

struct UnkType_109b6370_Box
{
    UnkType_109b6370_Vector Min;
    UnkType_109b6370_Vector Max;
};

class UnkType_109b6370
{
public:
    static int Unk_109b6370(const UnkType_109b6370_Vector& Point, const UnkType_109b6370_Box& Box);
};

// UnkType_109b6370::Unk_109b6370
int UnkType_109b6370::Unk_109b6370(const UnkType_109b6370_Vector& Point,
    const UnkType_109b6370_Box& Box)
{
    if ( Point.X >= Box.Min.X && Point.X <= Box.Max.X && Point.Y >= Box.Min.Y
        && Point.Y <= Box.Max.Y && Point.Z >= Box.Min.Z && Point.Z <= Box.Max.Z )
    {
        return 1;
    }
    return 0;
}
