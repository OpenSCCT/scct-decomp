// campaign_leaf_4698b0.cpp -- thiscall at VA 0x10d698b0: calls the stdcall function pointer at
// VA 0x1131a5c4 with the dword at offset 0 and its argument. All names are invented.

extern int (__stdcall* GUnk_1131a5c4)(int, int);

class UnkType_10d698b0
{
public:
    void Unk_10d698b0(int Value);

private:
    int unk_00;
};

// UnkType_10d698b0::Unk_10d698b0
void UnkType_10d698b0::Unk_10d698b0(int Value)
{
    GUnk_1131a5c4(unk_00, Value);
}
