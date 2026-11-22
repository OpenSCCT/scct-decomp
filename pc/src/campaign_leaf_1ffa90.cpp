// campaign_leaf_1ffa90.cpp -- method at VA 0x10affa90 taking four arguments: calls the method at VA
// 0x10d9e850 on the object its first argument points to, passing the value at 0x04 of this object;
// the other three arguments are unused. The class, member and method names are invented; the
// offsets and the addresses are the binary's.

class UnkType_10d9e850
{
public:
    void Unk_10d9e850(int Value);
};

class UnkType_10affa90
{
public:
    void Unk_10affa90(UnkType_10d9e850* Target, int Arg1, int Arg2, int Arg3);

private:
    int unk_00;
    int unk_04;
};

// UnkType_10affa90::Unk_10affa90
void UnkType_10affa90::Unk_10affa90(UnkType_10d9e850* Target, int Arg1, int Arg2, int Arg3)
{
    Target->Unk_10d9e850(unk_04);
}
