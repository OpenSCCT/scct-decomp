// campaign_leaf_007a90.cpp -- method at VA 0x10907a90: returns whether the free function at VA
// 0x10ccae30 returns 0 for this string (its characters at 0x00, or an empty string when the count
// at 0x04 is 0) and the string its argument points to. The class, member and function names are
// invented; the offsets and the address are the binary's.

int Unk_10ccae30(const unsigned short* A, const unsigned short* B);

class UnkType_10907a90
{
public:
    int Unk_10907a90(const unsigned short* Other);

private:
    unsigned short* unk_00;
    int unk_04;
};

// UnkType_10907a90::Unk_10907a90
int UnkType_10907a90::Unk_10907a90(const unsigned short* Other)
{
    return Unk_10ccae30(unk_04 ? unk_00 : L"", Other) == 0;
}
