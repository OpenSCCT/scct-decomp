// campaign_leaf_3ea100.cpp -- one function at file offset 0x3ea100, preferred VA 0x10cea100. It
// returns 1 when the product of the halfwords at 0x36 and 0x34 is nonzero, the word at 0x3c is
// set or bits 0xc00 of the word at 0x38 are clear, and the word at 0x20 is not 0x2a5. The class,
// method and member names are invented; the offsets and the bytes are the binary's.

class UnkType_10cea100
{
public:
    int Unk_10cea100() const;

    unsigned char unk_0[0x20];
    int unk_20;
    unsigned char unk_24[0x10];
    unsigned short unk_34;
    unsigned short unk_36;
    unsigned int unk_38;
    int unk_3c;
};

// UnkType_10cea100::Unk_10cea100
int UnkType_10cea100::Unk_10cea100() const
{
    return unk_36 * unk_34 != 0
        && ( unk_3c != 0 || ( unk_38 & 0xc00 ) == 0 )
        && unk_20 != 0x2a5;
}
