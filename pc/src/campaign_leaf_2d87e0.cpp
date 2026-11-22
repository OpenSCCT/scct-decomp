// campaign_leaf_2d87e0.cpp -- one function at file offset 0x2d87e0, preferred VA 0x10bd87e0. It
// searches the two 0x58-byte entries at offset 0x320 for one whose first word equals its argument
// and returns the word at offset 0x14 of that entry, or 0. The class, method and member names are
// invented; the offset and the bytes are the binary's.

struct UnkEntry
{
    int unk_0;
    unsigned char unk_4[0x14 - 0x4];
    int unk_14;
    unsigned char unk_18[0x58 - 0x18];
};

class UnkType_10bd87e0
{
public:
    unsigned char unk_0[0x320];
    UnkEntry unk_320[2];

    int Unk_10bd87e0(int Key);
};

// UnkType_10bd87e0::Unk_10bd87e0
int UnkType_10bd87e0::Unk_10bd87e0(int Key)
{
    for ( int i = 0; i < 2; i++ )
    {
        if ( unk_320[i].unk_0 == Key )
        {
            return unk_320[i].unk_14;
        }
    }
    return 0;
}
