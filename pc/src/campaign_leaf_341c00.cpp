// campaign_leaf_341c00.cpp -- one function at file offset 0x341c00, preferred VA 0x10c41c00. It
// stores its two arguments as the key-value pair at offset 0x414 selected by the index at offset
// 0x40c, advances that index, wrapping to 0 at 4, and returns 1. The class, method and member
// names are invented; the offset and the bytes are the binary's.

struct UnkPair
{
    int unk_0;
    int unk_4;
};

class UnkType_10c41c00
{
public:
    unsigned char unk_0[0x40c];
    int unk_40c;
    unsigned char unk_410[0x414 - 0x410];
    UnkPair unk_414[4];

    int Unk_10c41c00(int Key, int Value);
};

// UnkType_10c41c00::Unk_10c41c00
int UnkType_10c41c00::Unk_10c41c00(int Key, int Value)
{
    unk_414[unk_40c].unk_0 = Key;
    unk_414[unk_40c].unk_4 = Value;
    unk_40c++;
    if ( unk_40c >= 4 )
    {
        unk_40c = 0;
    }
    return 1;
}
