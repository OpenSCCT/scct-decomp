// campaign_leaf_72fdf0.cpp -- thiscall method at VA 0x1102fdf0: passes the data at VA 0x111e17a4 and the member
// at 0x10 to the cdecl function at VA 0x10f364f2. The class, method, function and global names are
// invented.

extern char GUnk_111e17a4[];
void Unk_10f364f2(const char* Data, int Value);

class UnkType_1102fdf0
{
public:
    void Unk_1102fdf0();

private:
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
    int unk_10;
};

// UnkType_1102fdf0::Unk_1102fdf0
void UnkType_1102fdf0::Unk_1102fdf0()
{
    Unk_10f364f2(GUnk_111e17a4, unk_10);
}
