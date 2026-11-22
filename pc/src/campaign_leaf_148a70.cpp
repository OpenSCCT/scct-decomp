// campaign_leaf_148a70.cpp -- one function at file offset 0x148a70, preferred VA 0x10a48a70. It
// stores its first three byte arguments at offsets 0x66, 0x65 and 0x64, and its fourth at 0x67,
// or 0xff in its place when the fourth is zero. The class, method and member names are invented;
// the offset and the bytes are the binary's.

class UnkType_10a48a70
{
public:
    unsigned char unk_0[0x64];
    unsigned char unk_64;
    unsigned char unk_65;
    unsigned char unk_66;
    unsigned char unk_67;

    void Unk_10a48a70(unsigned char First, unsigned char Second, unsigned char Third,
        unsigned char Fourth);
};

// UnkType_10a48a70::Unk_10a48a70
void UnkType_10a48a70::Unk_10a48a70(unsigned char First, unsigned char Second, unsigned char Third,
    unsigned char Fourth)
{
    unk_66 = First;
    unk_65 = Second;
    unk_64 = Third;
    if ( !Fourth )
    {
        unk_67 = 0xff;
    }
    else
    {
        unk_67 = Fourth;
    }
}
