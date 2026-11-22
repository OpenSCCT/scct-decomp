// campaign_leaf_483f40.cpp -- thiscall at VA 0x10d83f40: passes its four-byte by-value argument to
// the method at VA 0x10d99750 of the member at offset 0x18 and returns the result. All
// names are invented.

class UnkType_10d83f40_Param
{
public:
    UnkType_10d83f40_Param(const UnkType_10d83f40_Param& Other) : unk_00(Other.unk_00) {}

private:
    int unk_00;
};

class UnkType_10d99750
{
public:
    int Unk_10d99750(UnkType_10d83f40_Param Value);
};

class UnkType_10d83f40
{
public:
    int Unk_10d83f40(UnkType_10d83f40_Param Value);

private:
    unsigned char unk_00[0x18];
    UnkType_10d99750 unk_18;
};

// UnkType_10d83f40::Unk_10d83f40
int UnkType_10d83f40::Unk_10d83f40(UnkType_10d83f40_Param Value)
{
    return unk_18.Unk_10d99750(Value);
}
