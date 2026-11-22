// campaign_leaf_348250.cpp -- one function at file offset 0x348250, preferred VA 0x10c48250. It
// sets bit 0x1 of the flags at offset 0x44c, copies the word at offset 0x40c to 0x408 and the one
// at 0x440 to 0x444, and clears the word at offset 0x410. The class, method and member names are
// invented; the offset and the bytes are the binary's.

class UnkType_10c48250
{
public:
    unsigned char unk_0[0x408];
    int unk_408;
    int unk_40c;
    int unk_410;
    unsigned char unk_414[0x440 - 0x414];
    int unk_440;
    int unk_444;
    unsigned char unk_448[0x44c - 0x448];
    int unk_44c;

    void Unk_10c48250();
};

// UnkType_10c48250::Unk_10c48250
void UnkType_10c48250::Unk_10c48250()
{
    unk_44c |= 1;
    unk_408 = unk_40c;
    unk_444 = unk_440;
    unk_410 = 0;
}
