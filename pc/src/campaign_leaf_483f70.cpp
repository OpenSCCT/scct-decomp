// campaign_leaf_483f70.cpp -- thiscall at VA 0x10d83f70: passes its four-byte by-value argument to
// the method at VA 0x10d99ed0 of the member at offset 0x18 and returns the result. All
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

class UnkType_10d83f70
{
public:
    int Unk_10d83f70(UnkType_10d99ed0_Param Value);

private:
    unsigned char unk_00[0x18];
    UnkType_10d99ed0 unk_18;
};

// UnkType_10d83f70::Unk_10d83f70
int UnkType_10d83f70::Unk_10d83f70(UnkType_10d99ed0_Param Value)
{
    return unk_18.Unk_10d99ed0(Value);
}
