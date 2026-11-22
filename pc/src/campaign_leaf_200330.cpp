// campaign_leaf_200330.cpp -- method at VA 0x10b00330 taking four arguments: calls the free
// function at VA 0x10b039c0 with its first argument and the address of the member at 0x04; the
// other three arguments are unused. The class, member and function names are invented; the offsets
// and the addresses are the binary's.

class UnkType_10b00330_10d9e850;

class UnkType_10b00330_10b039c0
{
public:
    int unk_00;
    int unk_04;
};

void Unk_10b039c0(UnkType_10b00330_10d9e850* Target, UnkType_10b00330_10b039c0* Source);

class UnkType_10b00330
{
public:
    void Unk_10b00330(UnkType_10b00330_10d9e850* Target, int Arg1, int Arg2, int Arg3);

private:
    int unk_00;
    UnkType_10b00330_10b039c0 unk_04;
};

// UnkType_10b00330::Unk_10b00330
void UnkType_10b00330::Unk_10b00330(UnkType_10b00330_10d9e850* Target, int Arg1, int Arg2, int Arg3)
{
    Unk_10b039c0(Target, &unk_04);
}
