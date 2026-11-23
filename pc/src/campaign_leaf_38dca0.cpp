// campaign_leaf_38dca0.cpp -- method at VA 0x10c8dca0: returns 1 while the time from the free
// function at VA 0x10a3c6b0 is before the double at 0x50, and afterwards 1 less half the time
// elapsed since it. The class, member and function names are invented; the offsets, the
// constants and the address are the binary's.

double Unk_10a3c6b0();

class UnkType_10c8dca0
{
public:
    double Unk_10c8dca0();

private:
    char unk_0[0x50];
    double unk_50;
};

// UnkType_10c8dca0::Unk_10c8dca0
double UnkType_10c8dca0::Unk_10c8dca0()
{
    if ( Unk_10a3c6b0() < unk_50 )
    {
        return 1.0;
    }
    return 1.0 - ( Unk_10a3c6b0() - unk_50 ) * 0.5;
}
