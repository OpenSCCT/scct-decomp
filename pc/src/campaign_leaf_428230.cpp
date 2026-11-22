// campaign_leaf_428230.cpp -- one function at file offset 0x428230, preferred VA 0x10d28230. It
// returns 1 when a point of two signed halfwords lies inside the inclusive ranges 0x0-0x2 and
// 0x4-0x6 of the object. The class, method, structure and member names are invented; the
// offsets and the bytes are the binary's.

struct UnkType_10d28230_Point
{
    short unk_0;
    short unk_2;
};

class UnkType_10d28230
{
public:
    int Unk_10d28230(const UnkType_10d28230_Point& Point) const;

    short unk_0;
    short unk_2;
    short unk_4;
    short unk_6;
};

// UnkType_10d28230::Unk_10d28230
int UnkType_10d28230::Unk_10d28230(const UnkType_10d28230_Point& Point) const
{
    return Point.unk_0 >= unk_0 && Point.unk_0 <= unk_2
        && Point.unk_2 >= unk_4 && Point.unk_2 <= unk_6;
}
