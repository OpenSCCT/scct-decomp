// campaign_leaf_05c630.cpp -- method at VA 0x1095c630: passes the 8-byte value the free function at
// VA 0x10d90d10 returns to the method at VA 0x10df40a0. The class and function names are invented;
// the addresses are the binary's.

class UnkType_10d90d10_05c630
{
public:
    UnkType_10d90d10_05c630();

private:
    int unk_00;
    int unk_04;
};

UnkType_10d90d10_05c630 Unk_10d90d10();

class UnkType_1095c630
{
public:
    void Unk_1095c630();
    void Unk_10df40a0(UnkType_10d90d10_05c630 Value);
};

// UnkType_1095c630::Unk_1095c630
void UnkType_1095c630::Unk_1095c630()
{
    Unk_10df40a0(Unk_10d90d10());
}
