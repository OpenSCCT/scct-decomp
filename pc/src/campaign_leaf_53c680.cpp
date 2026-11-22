// campaign_leaf_53c680.cpp -- one function at file offset 0x53c680, preferred VA 0x10e3c680. It
// snaps three low/high pairs of words (0xc/0x10, 0x14/0x18, 0x1c/0x20) to a grid of 2^n, n being
// the word at 0x24: each low is rounded down into 0x48-0x50 and each high rounded up past its
// cell into 0x54-0x5c. The class, method and member names are invented; the offsets and the
// bytes are the binary's.

struct UnkRange
{
    int unk_0;
    int unk_4;
};

class UnkType_10e3c680
{
public:
    void Unk_10e3c680();

    unsigned char unk_0[0xc];
    UnkRange unk_c[3];
    int unk_24;
    unsigned char unk_28[0x20];
    int unk_48[3];
    int unk_54[3];
};

// UnkType_10e3c680::Unk_10e3c680
void UnkType_10e3c680::Unk_10e3c680()
{
    int Axis;

    for ( Axis = 0; Axis < 3; Axis++ )
    {
        int Shift = unk_24;

        unk_48[Axis] = ( unk_c[Axis].unk_0 >> Shift ) << Shift;
        unk_54[Axis] = ( ( unk_c[Axis].unk_4 >> Shift ) + 1 ) << Shift;
    }
}
