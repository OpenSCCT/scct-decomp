// campaign_leaf_53bbe0.cpp -- function at VA 0x10e3bbe0: calls the method at VA 0x10e38a80 on
// Target twelve times with fixed pairs of small numbers. guess: registers a table of pairings. All
// names are invented; the addresses and the numbers are the binary's.

class UnkType_10e3bbe0_Target
{
public:
    void Unk_10e38a80(int First, int Second);
};

// Unk_10e3bbe0
void Unk_10e3bbe0(UnkType_10e3bbe0_Target* Target)
{
    Target->Unk_10e38a80(0x4, 0x1);
    Target->Unk_10e38a80(0x5, 0x1);
    Target->Unk_10e38a80(0x6, 0x1);
    Target->Unk_10e38a80(0x7, 0x1);
    Target->Unk_10e38a80(0x8, 0x1);
    Target->Unk_10e38a80(0x17, 0x1);
    Target->Unk_10e38a80(0xb, 0x2);
    Target->Unk_10e38a80(0xa, 0x2);
    Target->Unk_10e38a80(0x13, 0x3);
    Target->Unk_10e38a80(0x1, 0x10);
    Target->Unk_10e38a80(0x12, 0xd);
    Target->Unk_10e38a80(0xe, 0xd);
}
