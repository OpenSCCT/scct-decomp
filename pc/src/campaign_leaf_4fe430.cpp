// campaign_leaf_4fe430.cpp -- one function at file offset 0x4fe430, preferred VA 0x10dfe430. It
// searches the eight-byte entries (data at 0x0, count at 0x4) from the last for one whose first
// word equals Key, removes it by moving the last entry into its place and returns 0; it returns
// 1 when there is none. The class, method, structure and member names are invented; the offsets
// and the bytes are the binary's.

struct UnkEntry
{
    int unk_0;
    int unk_4;
};

class UnkType_10dfe430
{
public:
    int Unk_10dfe430(const int& Key);

    UnkEntry* unk_0;
    int unk_4;
};

// UnkType_10dfe430::Unk_10dfe430
int UnkType_10dfe430::Unk_10dfe430(const int& Key)
{
    int Index;

    for ( Index = unk_4 - 1; Index >= 0; Index-- )
    {
        if ( unk_0[Index].unk_0 == Key )
        {
            unk_4--;
            unk_0[Index] = unk_0[unk_4];
            return 0;
        }
    }
    return 1;
}
