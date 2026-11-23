// campaign_leaf_08e7d0.cpp -- method at VA 0x1098e7d0: returns 1 when the method at VA 0x10aa7d00
// or the method at VA 0x10aa7d20 returns nonzero, otherwise 0. The class and method names are
// invented; the addresses are the binary's.

class UnkType_1098e7d0
{
public:
    int Unk_1098e7d0();
    int Unk_10aa7d00();
    int Unk_10aa7d20();
};

// UnkType_1098e7d0::Unk_1098e7d0
int UnkType_1098e7d0::Unk_1098e7d0()
{
    return Unk_10aa7d00() || Unk_10aa7d20();
}
