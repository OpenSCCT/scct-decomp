// campaign_leaf_4e99a0.cpp -- method at VA 0x10de99a0: writes the words at 0x00 and 0x04 to the
// stream that is its first argument (method at VA 0x10d9e850). The class, method, member and
// parameter names are invented; the offsets and the addresses are the binary's.

class UnkType_10de99a0_Writer
{
public:
    void Unk_10d9e810(unsigned short Value);
    void Unk_10d9e850(int Value);
};

class UnkType_10de99a0
{
public:
    void Unk_10de99a0(UnkType_10de99a0_Writer* Writer, int Arg1, int Arg2, int Arg3);

    int unk_00;
    int unk_04;
};

// UnkType_10de99a0::Unk_10de99a0
void UnkType_10de99a0::Unk_10de99a0(UnkType_10de99a0_Writer* Writer, int Arg1, int Arg2, int Arg3)
{
    Writer->Unk_10d9e850(unk_00);
    Writer->Unk_10d9e850(unk_04);
}
