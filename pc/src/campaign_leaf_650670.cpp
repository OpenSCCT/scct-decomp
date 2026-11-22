// campaign_leaf_650670.cpp -- one function at file offset 0x650670, preferred VA 0x10f50670. It
// clamps X to [0, unk_0 - 1] and Y to [0, unk_4 - 1] and returns Y * unk_0 + X, the index of a
// cell in a row-major grid. The class, method and member names are invented; the offset and the
// bytes are the binary's.

class UnkType_10f50670
{
public:
    int unk_0;
    int unk_4;

    int Unk_10f50670(int X, int Y);
};

// UnkType_10f50670::Unk_10f50670
int UnkType_10f50670::Unk_10f50670(int X, int Y)
{
    if ( X < 0 )
    {
        X = 0;
    }
    if ( Y < 0 )
    {
        Y = 0;
    }
    if ( X >= unk_0 )
    {
        X = unk_0 - 1;
    }
    if ( Y >= unk_4 )
    {
        Y = unk_4 - 1;
    }
    return Y * unk_0 + X;
}
