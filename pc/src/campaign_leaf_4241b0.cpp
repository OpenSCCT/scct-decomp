// campaign_leaf_4241b0.cpp -- one function at file offset 0x4241b0, preferred VA 0x10d241b0. A
// constructor taking two bytes: it stores them at 0x15 and 0x14 and zeroes the words at 0x4-0x10
// and the halfwords at 0x16 and 0x18. The class, member and parameter names are invented; the
// offsets and the bytes are the binary's.

class UnkType_10d241b0
{
public:
    UnkType_10d241b0(unsigned char First, unsigned char Second);

    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;
    int unk_10;
    unsigned char unk_14;
    unsigned char unk_15;
    unsigned short unk_16;
    unsigned short unk_18;
};

// UnkType_10d241b0::UnkType_10d241b0
UnkType_10d241b0::UnkType_10d241b0(unsigned char First, unsigned char Second)
{
    unk_4 = 0;
    unk_8 = 0;
    unk_c = 0;
    unk_10 = 0;
    unk_14 = Second;
    unk_15 = First;
    unk_16 = 0;
    unk_18 = 0;
}
