// campaign_leaf_4ec450.cpp -- one function at file offset 0x4ec450, preferred VA 0x10dec450. A
// constructor: it stores three words at 0x0-0x8, a halfword-and-word structure at 0xc, a byte at
// 0x14 and clears the byte at 0x15. The class, structure, member and parameter names are
// invented; the offsets and the bytes are the binary's.

struct UnkPair
{
    short unk_0;
    int unk_4;
};

class UnkType_10dec450
{
public:
    UnkType_10dec450(int First, int Second, int Third, const UnkPair& Fourth, unsigned char Fifth);

    int unk_0;
    int unk_4;
    int unk_8;
    UnkPair unk_c;
    unsigned char unk_14;
    unsigned char unk_15;
};

// UnkType_10dec450::UnkType_10dec450
UnkType_10dec450::UnkType_10dec450(int First, int Second, int Third, const UnkPair& Fourth,
                         unsigned char Fifth)
{
    unk_0 = First;
    unk_4 = Second;
    unk_8 = Third;
    unk_c.unk_0 = Fourth.unk_0;
    unk_c.unk_4 = Fourth.unk_4;
    unk_14 = Fifth;
    unk_15 = 0;
}
