// campaign_leaf_474780.cpp -- thiscall at VA 0x10d74780: when the dword at offset 8 is set, passes it
// to the stdcall function at VA 0x1103c870 and clears the dwords at offsets 8 and 0x0c. All names
// are invented.

void __stdcall Unk_1103c870(int Value);

class UnkType_10d74780
{
public:
    void Unk_10d74780();

private:
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
};

// UnkType_10d74780::Unk_10d74780
void UnkType_10d74780::Unk_10d74780()
{
    if (unk_08) {
        Unk_1103c870(unk_08);
        unk_08 = 0;
        unk_0c = 0;
    }
}
