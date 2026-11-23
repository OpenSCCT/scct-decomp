// campaign_leaf_202e50.cpp -- thiscall method at VA 0x10b02e50 taking four arguments, of which only
// the first is read. It passes the word at offset 0x04 of each of the six 0x154-byte entries
// starting at 0x00 to the first argument's method at VA 0x10d9e970. The class, method and member
// names are invented.

class UnkType_10b02e50_Target
{
public:
    void Unk_10d9e970(int Value);
};

struct UnkType_10b02e50_Entry
{
    int unk_000;
    int unk_004;
    char unk_008[0x154 - 0x008];
};

class UnkType_10b02e50
{
public:
    void Unk_10b02e50(UnkType_10b02e50_Target* Target, int First, int Second, int Third);

private:
    UnkType_10b02e50_Entry unk_000[6];
};

// UnkType_10b02e50::Unk_10b02e50
void UnkType_10b02e50::Unk_10b02e50(UnkType_10b02e50_Target* Target, int First, int Second,
                                    int Third)
{
    Target->Unk_10d9e970(unk_000[0].unk_004);
    Target->Unk_10d9e970(unk_000[1].unk_004);
    Target->Unk_10d9e970(unk_000[2].unk_004);
    Target->Unk_10d9e970(unk_000[3].unk_004);
    Target->Unk_10d9e970(unk_000[4].unk_004);
    Target->Unk_10d9e970(unk_000[5].unk_004);
}
