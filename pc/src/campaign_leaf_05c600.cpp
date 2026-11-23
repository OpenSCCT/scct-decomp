// campaign_leaf_05c600.cpp -- method at VA 0x1095c600: passes the 8-byte value the free function at
// VA 0x10d90d10 returns to the method at VA 0x10df3840. The class and function names are invented;
// the addresses are the binary's.

class UnkType_10d90d10_05c600
{
public:
    UnkType_10d90d10_05c600();

private:
    int unk_00;
    int unk_04;
};

UnkType_10d90d10_05c600 Unk_10d90d10();

class UnkType_1095c600
{
public:
    void Unk_1095c600();
    void Unk_10df3840(UnkType_10d90d10_05c600 Value);
};

// UnkType_1095c600::Unk_1095c600
void UnkType_1095c600::Unk_1095c600()
{
    Unk_10df3840(Unk_10d90d10());
}
