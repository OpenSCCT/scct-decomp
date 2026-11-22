// campaign_leaf_486ab0.cpp -- free function at VA 0x10d86ab0: calls the free function at
// VA 0x10d86600 with its first argument, its four-byte by-value second argument and 0, and returns
// the result. All names are invented.

class UnkType_10d86ab0_Param
{
public:
    UnkType_10d86ab0_Param(const UnkType_10d86ab0_Param& Other) : unk_00(Other.unk_00) {}

private:
    int unk_00;
};

int Unk_10d86600(int Value, UnkType_10d86ab0_Param Param, int Flags);

// Unk_10d86ab0
int Unk_10d86ab0(int Value, UnkType_10d86ab0_Param Param)
{
    return Unk_10d86600(Value, Param, 0);
}
