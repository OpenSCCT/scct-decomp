// campaign_leaf_05d8a0.cpp -- method at VA 0x1095d8a0: passes 0 to the method at VA 0x10d87c80,
// then passes 0 to the method at VA 0x10d8eee0 of the member at 0x04 and calls that member's method
// at VA 0x10d8edb0. The class, member and method names are invented; the offset and the addresses
// are the binary's.

class UnkType_10d8eee0_05d8a0
{
public:
    void Unk_10d8eee0(const int& Value);
    void Unk_10d8edb0();
};

class UnkType_1095d8a0
{
public:
    void Unk_1095d8a0();
    void Unk_10d87c80(int Value);

private:
    int unk_00;
    UnkType_10d8eee0_05d8a0 unk_04;
};

// UnkType_1095d8a0::Unk_1095d8a0
void UnkType_1095d8a0::Unk_1095d8a0()
{
    Unk_10d87c80(0);
    unk_04.Unk_10d8eee0(0);
    unk_04.Unk_10d8edb0();
}
