// campaign_leaf_061c00.cpp -- method at VA 0x10961c00: when the value at 0x00 is 0, passes 0 to the
// method at VA 0x10d8eee0 of the member at 0x04; otherwise calls the methods at VA 0x10961ad0 and
// 0x10961b50 (with 1). The class, member and method names are invented; the offsets and the
// addresses are the binary's.

class UnkType_10d8eee0_061c00
{
public:
    void Unk_10d8eee0(const int& Value);
};

class UnkType_10961c00
{
public:
    void Unk_10961c00();
    void Unk_10961ad0();
    void Unk_10961b50(int Value);

private:
    int unk_00;
    UnkType_10d8eee0_061c00 unk_04;
};

// UnkType_10961c00::Unk_10961c00
void UnkType_10961c00::Unk_10961c00()
{
    if ( !unk_00 )
    {
        unk_04.Unk_10d8eee0(0);
    }
    else
    {
        Unk_10961ad0();
        Unk_10961b50(1);
    }
}
