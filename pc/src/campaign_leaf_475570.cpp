// campaign_leaf_475570.cpp -- one function at file offset 0x475570, preferred VA 0x10d75570. It
// returns 1 unless the floats at 0x4 and 0x8 equal the argument's. The class, method and member names are invented; the offsets and the
// bytes are the binary's.

class UnkType_10d75570
{
public:
    int Unk_10d75570(const UnkType_10d75570& Other) const;

    int unk_0;
    float unk_4;
    float unk_8;
};

// UnkType_10d75570::Unk_10d75570
int UnkType_10d75570::Unk_10d75570(const UnkType_10d75570& Other) const
{
    return unk_4 != Other.unk_4 || unk_8 != Other.unk_8;
}
