// campaign_leaf_46c830.cpp -- thiscall at VA 0x10d6c830: passes the dword at offset 8 to the
// stdcall function at VA 0x1103c870, then clears the dwords at offsets 4 and 0. All names are
// invented.

void __stdcall Unk_1103c870(int Value);

class UnkType_10d6c830
{
public:
    void Unk_10d6c830();

private:
    int unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_10d6c830::Unk_10d6c830
void UnkType_10d6c830::Unk_10d6c830()
{
    Unk_1103c870(unk_08);
    unk_04 = 0;
    unk_00 = 0;
}
