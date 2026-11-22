// campaign_leaf_727bd0.cpp -- thiscall method at VA 0x11027bd0: passes the data at VA 0x111e12c8 and the member
// at 0x0c to the cdecl function at VA 0x10f364f2. The class, method, function and global names are
// invented.

extern char GUnk_111e12c8[];
void Unk_10f364f2(const char* Data, int Value);

class UnkType_11027bd0
{
public:
    void Unk_11027bd0();

private:
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
};

// UnkType_11027bd0::Unk_11027bd0
void UnkType_11027bd0::Unk_11027bd0()
{
    Unk_10f364f2(GUnk_111e12c8, unk_0c);
}
