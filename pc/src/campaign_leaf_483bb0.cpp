// campaign_leaf_483bb0.cpp -- free function at VA 0x10d83bb0: passes its four-byte by-value
// second argument to the method at VA 0x10db7f30 of its first argument and returns the result.
// All names are invented.

class UnkType_10d83bb0_Param
{
public:
    UnkType_10d83bb0_Param(const UnkType_10d83bb0_Param& Other) : unk_00(Other.unk_00) {}

private:
    int unk_00;
};

class UnkType_10db7f30
{
public:
    int Unk_10db7f30(UnkType_10d83bb0_Param Value);
};

// Unk_10d83bb0
int Unk_10d83bb0(UnkType_10db7f30* Object, UnkType_10d83bb0_Param Value)
{
    return Object->Unk_10db7f30(Value);
}
