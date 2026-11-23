// campaign_leaf_38dc70.cpp -- method at VA 0x10c8dc70: when the time from the free function at
// VA 0x10a3c6b0 is not after the double at 0x50, stores that time at 0x50 and the time two
// seconds later at 0x48. The class, member and function names are invented; the offsets, the
// constant and the address are the binary's.

double Unk_10a3c6b0();

class UnkType_10c8dc70
{
public:
    void Unk_10c8dc70();

private:
    char unk_0[0x48];
    double unk_48;
    double unk_50;
};

// UnkType_10c8dc70::Unk_10c8dc70
void UnkType_10c8dc70::Unk_10c8dc70()
{
    if ( Unk_10a3c6b0() <= unk_50 )
    {
        unk_50 = Unk_10a3c6b0();
        unk_48 = unk_50 + 2.0;
    }
}
