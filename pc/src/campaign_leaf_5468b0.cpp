// campaign_leaf_5468b0.cpp -- one function at file offset 0x5468b0, preferred VA 0x10e468b0. A
// constructor: it clears the halfword at 0x4 of each of the eight six-byte entries at 0x20, the
// words at 0x50 and 0x54 and the byte at 0x58. The class, structure and member names are
// invented; the offsets and the bytes are the binary's.

struct UnkType_10e468b0_Entry
{
    UnkType_10e468b0_Entry()
    {
        unk_4 = 0;
    }

    unsigned short unk_0;
    unsigned short unk_2;
    unsigned short unk_4;
};

class UnkType_10e468b0
{
public:
    UnkType_10e468b0();

    unsigned char unk_0[0x20];
    UnkType_10e468b0_Entry unk_20[8];
    int unk_50;
    int unk_54;
    unsigned char unk_58;
};

// UnkType_10e468b0::UnkType_10e468b0
UnkType_10e468b0::UnkType_10e468b0()
{
    unk_54 = 0;
    unk_50 = 0;
    unk_58 = 0;
}
