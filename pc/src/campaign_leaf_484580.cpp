// campaign_leaf_484580.cpp -- thiscall at VA 0x10d84580: passes the four-byte object at offset
// 0x0c by value to the free function at VA 0x10d7d9f0 and returns its result. All names are
// invented.

class UnkType_10d7d9f0_Param
{
public:
    UnkType_10d7d9f0_Param(const UnkType_10d7d9f0_Param& Other) : unk_00(Other.unk_00) {}

private:
    int unk_00;
};

int Unk_10d7d9f0(UnkType_10d7d9f0_Param Value);

class UnkType_10d84580
{
public:
    int Unk_10d84580();

private:
    unsigned char unk_00[0x0c];
    UnkType_10d7d9f0_Param unk_0c;
};

// UnkType_10d84580::Unk_10d84580
int UnkType_10d84580::Unk_10d84580()
{
    return Unk_10d7d9f0(unk_0c);
}
