// campaign_leaf_34d8f0.cpp -- one function at file offset 0x34d8f0, preferred VA 0x10c4d8f0. It
// calls the method at 0x10bee290, passes each of the kinds 0 to 4 to the method at 0x10c4d240,
// and then calls the methods at 0x10c4d370 and 0x10c4c9c0. The class, method and parameter names
// are invented; the constants and the bytes are the binary's.

class UnkType_10c4d8f0
{
public:
    void Unk_10bee290();
    void Unk_10c4c9c0();
    void Unk_10c4d240(const unsigned char& Kind);
    void Unk_10c4d370();
    void Unk_10c4d8f0();
};

// UnkType_10c4d8f0::Unk_10c4d8f0
void UnkType_10c4d8f0::Unk_10c4d8f0()
{
    Unk_10bee290();
    Unk_10c4d240(0);
    Unk_10c4d240(1);
    Unk_10c4d240(2);
    Unk_10c4d240(3);
    Unk_10c4d240(4);
    Unk_10c4d370();
    Unk_10c4c9c0();
}
