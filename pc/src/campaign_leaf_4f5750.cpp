// campaign_leaf_4f5750.cpp -- method at VA 0x10df5750: writes the word at 0x00 (method at VA
// 0x10d9e850) and the sixteen-bit value at 0x04 (method at VA 0x10d9e810) to the stream that is its
// first argument. The class, method, member and parameter names are invented; the offsets and the
// addresses are the binary's.

class UnkType_10df5750_Writer
{
public:
    void Unk_10d9e810(unsigned short Value);
    void Unk_10d9e850(int Value);
};

class UnkType_10df5750
{
public:
    void Unk_10df5750(UnkType_10df5750_Writer* Writer, int Arg1, int Arg2, int Arg3);

    int unk_00;
    unsigned short unk_04;
};

// UnkType_10df5750::Unk_10df5750
void UnkType_10df5750::Unk_10df5750(UnkType_10df5750_Writer* Writer, int Arg1, int Arg2, int Arg3)
{
    Writer->Unk_10d9e850(unk_00);
    Writer->Unk_10d9e810(unk_04);
}
