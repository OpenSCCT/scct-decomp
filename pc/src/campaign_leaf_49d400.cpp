// campaign_leaf_49d400.cpp -- thiscall at VA 0x10d9d400: passes the four-byte object at offset 0
// by value to the free function at VA 0x10db6370 and returns its result. All names are invented.

class UnkType_10db6370_Param
{
public:
    UnkType_10db6370_Param(const UnkType_10db6370_Param& Other) : unk_00(Other.unk_00) {}

private:
    int unk_00;
};

int Unk_10db6370(UnkType_10db6370_Param Value);

class UnkType_10d9d400
{
public:
    int Unk_10d9d400();

private:
    UnkType_10db6370_Param unk_00;
};

// UnkType_10d9d400::Unk_10d9d400
int UnkType_10d9d400::Unk_10d9d400()
{
    return Unk_10db6370(unk_00);
}
