// campaign_leaf_1d2090.cpp -- free function at VA 0x10ad2090: returns, by value, a copy of the
// global at VA 0x1120aa44, made with the 12-byte class's copy constructor at VA 0x1090b9a0. The
// class, function and global names are invented; the addresses are the binary's.

class UnkType_1090b9a0
{
public:
    UnkType_1090b9a0(const UnkType_1090b9a0& Other);

private:
    int unk_00;
    int unk_04;
    int unk_08;
};

extern UnkType_1090b9a0 GUnk_1120aa44;

// Unk_10ad2090
UnkType_1090b9a0 Unk_10ad2090()
{
    return GUnk_1120aa44;
}
