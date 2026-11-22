// campaign_leaf_4e0630.cpp -- thiscall at VA 0x10de0630: passes its eight-byte by-value argument
// by reference to the method at VA 0x10d95f50 of the member at offset 0xa4. All names are
// invented.

struct UnkType_10de0630_Param
{
    int unk_00;
    int unk_04;
};

class UnkType_10d95f50
{
public:
    void Unk_10d95f50(const UnkType_10de0630_Param& Value);
};

class UnkType_10de0630
{
public:
    void Unk_10de0630(UnkType_10de0630_Param Value);

private:
    unsigned char unk_00[0xa4];
    UnkType_10d95f50 unk_a4;
};

// UnkType_10de0630::Unk_10de0630
void UnkType_10de0630::Unk_10de0630(UnkType_10de0630_Param Value)
{
    unk_a4.Unk_10d95f50(Value);
}
