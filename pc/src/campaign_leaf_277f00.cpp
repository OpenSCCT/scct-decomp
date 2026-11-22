// campaign_leaf_277f00.cpp -- a member function at VA 0x10b77f00: when the pointer at 0x14 and the
// int at 0x20 are both non-zero it returns the byte result of the member at VA 0x10ad5970 of the
// pointer's object, given the int; otherwise 0. The class, method and member names are invented;
// the offsets and addresses are the binary's.

class UnkType_10ad5970
{
public:
    unsigned char Unk_10ad5970(int Value);
};

class UnkType_10b77f00
{
public:
    int Unk_10b77f00();

private:
    unsigned char unk_00[0x14];
    UnkType_10ad5970* unk_14;
    int unk_18;
    int unk_1c;
    int unk_20;
};

// UnkType_10b77f00::Unk_10b77f00
int UnkType_10b77f00::Unk_10b77f00()
{
    if ( unk_14 && unk_20 )
    {
        return unk_14->Unk_10ad5970(unk_20);
    }
    return 0;
}
