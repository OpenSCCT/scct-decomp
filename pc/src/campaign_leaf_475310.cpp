// campaign_leaf_475310.cpp -- thiscall at VA 0x10d75310: when the dword at offset 8 is set, passes it
// to the stdcall function at VA 0x1103c870 and clears the dwords at offsets 8 and 0x0c. All names
// are invented.

void __stdcall Unk_1103c870(int Value);

class UnkType_10d75310
{
public:
    void Unk_10d75310();

private:
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
};

// UnkType_10d75310::Unk_10d75310
void UnkType_10d75310::Unk_10d75310()
{
    if (unk_08) {
        Unk_1103c870(unk_08);
        unk_08 = 0;
        unk_0c = 0;
    }
}
