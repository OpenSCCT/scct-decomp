// campaign_leaf_4f8b30.cpp -- method at VA 0x10df8b30: writes the sixteen-bit value at 0x04, the
// word at 0xb0 and the sixteen-bit value at 0x204 to the stream that is its first argument (methods
// at VA 0x10d9e810 and 0x10d9e850). The class, method, member and parameter names are invented; the
// offsets and the addresses are the binary's.

class UnkType_10df8b30_Writer
{
public:
    void Unk_10d9e810(unsigned short Value);
    void Unk_10d9e850(int Value);
};

class UnkType_10df8b30
{
public:
    void Unk_10df8b30(UnkType_10df8b30_Writer* Writer, int Arg1, int Arg2, int Arg3);

    unsigned char unk_00[0x04];
    unsigned short unk_04;
    unsigned char unk_06[0xb0 - 0x06];
    int unk_b0;
    unsigned char unk_b4[0x204 - 0xb4];
    unsigned short unk_204;
};

// UnkType_10df8b30::Unk_10df8b30
void UnkType_10df8b30::Unk_10df8b30(UnkType_10df8b30_Writer* Writer, int Arg1, int Arg2, int Arg3)
{
    Writer->Unk_10d9e810(unk_04);
    Writer->Unk_10d9e850(unk_b0);
    Writer->Unk_10d9e810(unk_204);
}
