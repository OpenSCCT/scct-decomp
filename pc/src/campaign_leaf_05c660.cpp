// campaign_leaf_05c660.cpp -- method at VA 0x1095c660: passes the 8-byte value the free function at
// VA 0x10d90d10 returns to the method at VA 0x10df3fd0. The class and function names are invented;
// the addresses are the binary's.

class UnkType_10d90d10_05c660
{
public:
    UnkType_10d90d10_05c660();

private:
    int unk_00;
    int unk_04;
};

UnkType_10d90d10_05c660 Unk_10d90d10();

class UnkType_1095c660
{
public:
    void Unk_1095c660();
    void Unk_10df3fd0(UnkType_10d90d10_05c660 Value);
};

// UnkType_1095c660::Unk_1095c660
void UnkType_1095c660::Unk_1095c660()
{
    Unk_10df3fd0(Unk_10d90d10());
}
