// campaign_leaf_4f9d00.cpp -- method at VA 0x10df9d00: calls the method at VA 0x10d9e850 on its
// first argument with the first word of each of the six 0x154-byte entries at 0x04. The class,
// method and member names are invented; the offsets and the address are the binary's.

class UnkType_10df9d00_Entry
{
public:
    int unk_00;
    unsigned char unk_04[0x150];
};

class UnkType_10df9d00_Target
{
public:
    void Unk_10d9e850(int Value);
};

class UnkType_10df9d00
{
public:
    void Unk_10df9d00(UnkType_10df9d00_Target* Target, int Arg1, int Arg2, int Arg3);

    int unk_00;
    UnkType_10df9d00_Entry unk_04[6];
};

// UnkType_10df9d00::Unk_10df9d00
void UnkType_10df9d00::Unk_10df9d00(UnkType_10df9d00_Target* Target, int Arg1, int Arg2, int Arg3)
{
    Target->Unk_10d9e850(unk_04[0].unk_00);
    Target->Unk_10d9e850(unk_04[1].unk_00);
    Target->Unk_10d9e850(unk_04[2].unk_00);
    Target->Unk_10d9e850(unk_04[3].unk_00);
    Target->Unk_10d9e850(unk_04[4].unk_00);
    Target->Unk_10d9e850(unk_04[5].unk_00);
}
