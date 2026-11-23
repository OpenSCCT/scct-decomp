// campaign_leaf_1d63e0.cpp -- thiscall method at VA 0x10ad63e0. It asks the object returned by the
// function at VA 0x10adb390 for a width and a height (its method at VA 0x10adb4a0), falls back to
// 640 by 480 when either is not positive, and passes the centre point, two 16-bit coordinates, to
// the method at VA 0x10ad5b50. The class, method and member names are invented.

class UnkType_10ad63e0_Source
{
public:
    void Unk_10adb4a0(int* Width, int* Height);
};

UnkType_10ad63e0_Source* Unk_10adb390();

struct UnkType_10ad63e0_Point
{
    short X;
    short Y;
};

class UnkType_10ad63e0
{
public:
    void Unk_10ad63e0();
    void Unk_10ad5b50(UnkType_10ad63e0_Point* Point);
};

// UnkType_10ad63e0::Unk_10ad63e0
void UnkType_10ad63e0::Unk_10ad63e0()
{
    int Width = 0;
    int Height = 0;
    Unk_10adb390()->Unk_10adb4a0(&Width, &Height);
    if ( Width <= 0 || Height <= 0 )
    {
        Width = 640;
        Height = 480;
    }
    UnkType_10ad63e0_Point Center;
    Center.X = Width / 2;
    Center.Y = Height / 2;
    Unk_10ad5b50(&Center);
}
