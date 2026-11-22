// campaign_leaf_33d730.cpp -- a member function at VA 0x10c3d730 that calls the member at VA
// 0x10c3d5f0 and then passes its argument to the member at VA 0x10bef740. The class, method and
// parameter names are invented; the addresses are the binary's.

class UnkType_10c3d730
{
public:
    void Unk_10bef740(int Value);
    void Unk_10c3d5f0();
    void Unk_10c3d730(int Value);
};

// UnkType_10c3d730::Unk_10c3d730
void UnkType_10c3d730::Unk_10c3d730(int Value)
{
    Unk_10c3d5f0();
    Unk_10bef740(Value);
}
