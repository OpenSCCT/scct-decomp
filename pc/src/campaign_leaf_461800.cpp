// campaign_leaf_461800.cpp -- one function at file offset 0x461800, preferred VA 0x10d61800. It
// moves a rectangle of signed halfwords (0x0-0x2 and 0x4-0x6) so that it starts at the given
// point, keeping its extents. The class, method, structure and member names are invented; the
// offsets and the bytes are the binary's.

struct UnkType_10d61800_Point
{
    short unk_0;
    short unk_2;
};

class UnkType_10d61800
{
public:
    void Unk_10d61800(const UnkType_10d61800_Point& Point);

    short unk_0;
    short unk_2;
    short unk_4;
    short unk_6;
};

// UnkType_10d61800::Unk_10d61800
void UnkType_10d61800::Unk_10d61800(const UnkType_10d61800_Point& Point)
{
    int Width = unk_2 - unk_0;
    int Height = unk_6 - unk_4;

    unk_0 = Point.unk_0;
    unk_4 = Point.unk_2;
    unk_2 = unk_0 + Width;
    unk_6 = unk_4 + Height;
}
