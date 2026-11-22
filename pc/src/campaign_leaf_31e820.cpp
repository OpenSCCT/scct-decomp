// campaign_leaf_31e820.cpp -- one function at file offset 0x31e820, preferred VA 0x10c1e820. It
// returns 1 when its argument is non-null and is the first word, or the non-null second word, of
// a 0x4c-byte entry of the array at offset 0x34 (count at 0x38); otherwise 0. The class, method and
// member names are invented; the offset and the bytes are the binary's.

struct UnkType_10c1e820_Entry
{
    void* unk_0;
    void* unk_4;
    unsigned char unk_8[0x4c - 0x8];
};

class UnkType_10c1e820
{
public:
    unsigned char unk_0[0x34];
    UnkType_10c1e820_Entry* unk_34;
    int unk_38;

    int Unk_10c1e820(void* Key);
};

// UnkType_10c1e820::Unk_10c1e820
int UnkType_10c1e820::Unk_10c1e820(void* Key)
{
    if ( !Key )
    {
        return 0;
    }
    for ( int i = 0; i < unk_38; i++ )
    {
        if ( Key == unk_34[i].unk_0 || ( unk_34[i].unk_4 && Key == unk_34[i].unk_4 ) )
        {
            return 1;
        }
    }
    return 0;
}
