// campaign_leaf_4eb990.cpp -- thiscall at VA 0x10deb990: passes its eight-byte by-value argument
// by reference to the method at VA 0x10d95f50 of the member at offset 0x0c. All names are
// invented.

struct UnkType_10deb990_Param
{
    int unk_00;
    int unk_04;
};

class UnkType_10d95f50
{
public:
    void Unk_10d95f50(const UnkType_10deb990_Param& Value);
};

class UnkType_10deb990
{
public:
    void Unk_10deb990(UnkType_10deb990_Param Value);

private:
    unsigned char unk_00[0x0c];
    UnkType_10d95f50 unk_0c;
};

// UnkType_10deb990::Unk_10deb990
void UnkType_10deb990::Unk_10deb990(UnkType_10deb990_Param Value)
{
    unk_0c.Unk_10d95f50(Value);
}
