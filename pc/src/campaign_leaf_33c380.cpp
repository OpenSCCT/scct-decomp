// campaign_leaf_33c380.cpp -- one function at file offset 0x33c380, preferred VA 0x10c3c380. It
// returns by value the 12-byte value at offset 0x56c when the word its argument points to is 1,
// else the one at offset 0x578. The class, method and member names are invented; the offset and
// the bytes are the binary's.

struct UnkTriple
{
    int unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10c3c380
{
public:
    unsigned char unk_0[0x56c];
    UnkTriple unk_56c;
    UnkTriple unk_578;

    UnkTriple Unk_10c3c380(const int& Kind) const;
};

// UnkType_10c3c380::Unk_10c3c380
UnkTriple UnkType_10c3c380::Unk_10c3c380(const int& Kind) const
{
    if ( Kind == 1 )
    {
        return unk_56c;
    }
    return unk_578;
}
