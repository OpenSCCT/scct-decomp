// campaign_leaf_483f20.cpp -- thiscall at VA 0x10d83f20: passes its four-byte by-value argument to
// the method at VA 0x10d99ed0 of the member at offset 0x30 and returns the result. All
// names are invented.

class UnkType_10d99ed0_Param
{
public:
    UnkType_10d99ed0_Param(const UnkType_10d99ed0_Param& Other) : unk_00(Other.unk_00) {}

private:
    int unk_00;
};

class UnkType_10d99ed0
{
public:
    int Unk_10d99ed0(UnkType_10d99ed0_Param Value);
};

class UnkType_10d83f20
{
public:
    int Unk_10d83f20(UnkType_10d99ed0_Param Value);

private:
    unsigned char unk_00[0x30];
    UnkType_10d99ed0 unk_30;
};

// UnkType_10d83f20::Unk_10d83f20
int UnkType_10d83f20::Unk_10d83f20(UnkType_10d99ed0_Param Value)
{
    return unk_30.Unk_10d99ed0(Value);
}
