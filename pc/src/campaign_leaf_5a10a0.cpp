// campaign_leaf_5a10a0.cpp -- thiscall method at VA 0x10ea10a0 with one unused argument: stores the
// float result of the method at VA 0x10ea0e90 at 0x10 and that of VA 0x10ea0ef0 at 0x0c. The class
// and method names are invented.

class UnkType_10ea10a0
{
public:
    float Unk_10ea0e90();
    float Unk_10ea0ef0();
    void Unk_10ea10a0(int Unused);

private:
    int unk_00;
    int unk_04;
    int unk_08;
    float unk_0c;
    float unk_10;
};

// UnkType_10ea10a0::Unk_10ea10a0
void UnkType_10ea10a0::Unk_10ea10a0(int Unused)
{
    unk_10 = Unk_10ea0e90();
    unk_0c = Unk_10ea0ef0();
}
