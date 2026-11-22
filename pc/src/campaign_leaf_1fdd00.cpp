// campaign_leaf_1fdd00.cpp -- method at VA 0x10afdd00 taking four arguments: calls the free
// function at VA 0x10afea40 with its first argument and the address of the member at 0x04; the
// other three arguments are unused. The class, member and function names are invented; the offsets
// and the addresses are the binary's.

class UnkType_10afdd00_04
{
public:
    int unk_00;
};

void Unk_10afea40(int Value, UnkType_10afdd00_04* Member);

class UnkType_10afdd00
{
public:
    void Unk_10afdd00(int Value, int Arg1, int Arg2, int Arg3);

private:
    int unk_00;
    UnkType_10afdd00_04 unk_04;
};

// UnkType_10afdd00::Unk_10afdd00
void UnkType_10afdd00::Unk_10afdd00(int Value, int Arg1, int Arg2, int Arg3)
{
    Unk_10afea40(Value, &unk_04);
}
