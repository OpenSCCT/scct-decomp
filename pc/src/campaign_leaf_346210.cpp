// campaign_leaf_346210.cpp -- one function at file offset 0x346210, preferred VA 0x10c46210. It
// takes the first byte of the 24-byte entry of its argument's array at offset 0x414 selected by
// the argument's word at offset 0x420, and returns 1 when it equals either byte of the 4-byte
// entry of this object's array at offset 0x438 selected by the word at offset 0x42c, else 0. The
// class, method and member names are invented; the offset and the bytes are the binary's.

struct UnkWideEntry
{
    unsigned char unk_0;
    unsigned char unk_1[23];
};

struct UnkPairEntry
{
    unsigned char unk_0;
    unsigned char unk_1;
    unsigned char unk_2[2];
};

class UnkType_10c46210
{
public:
    unsigned char unk_0[0x414];
    UnkWideEntry* unk_414;
    unsigned char unk_418[0x420 - 0x418];
    int unk_420;
    unsigned char unk_424[0x42c - 0x424];
    int unk_42c;
    unsigned char unk_430[0x438 - 0x430];
    UnkPairEntry* unk_438;

    int Unk_10c46210(const UnkType_10c46210* Other);
};

// UnkType_10c46210::Unk_10c46210
int UnkType_10c46210::Unk_10c46210(const UnkType_10c46210* Other)
{
    int Value = Other->unk_414[Other->unk_420].unk_0;
    UnkPairEntry* Entry = &unk_438[unk_42c];
    if ( Value == Entry->unk_0 || Value == Entry->unk_1 )
    {
        return 1;
    }
    return 0;
}
