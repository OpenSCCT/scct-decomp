// campaign_leaf_31e870.cpp -- one function at file offset 0x31e870, preferred VA 0x10c1e870. It
// returns 1 when a 0x4c-byte entry of either the array at offset 0x34 (count at 0x38) or the one
// at offset 0x40 (count at 0x44) has its first argument as first word and its second argument as
// the byte at offset 0x8; otherwise 0. The class, method and member names are invented; the offset
// and the bytes are the binary's.

struct UnkType_10c1e870_Entry
{
    void* unk_0;
    int unk_4;
    unsigned char unk_8;
    unsigned char unk_9[0x4c - 0x9];
};

class UnkType_10c1e870
{
public:
    unsigned char unk_0[0x34];
    UnkType_10c1e870_Entry* unk_34;
    int unk_38;
    unsigned char unk_3c[0x40 - 0x3c];
    UnkType_10c1e870_Entry* unk_40;
    int unk_44;

    int Unk_10c1e870(void* Key, int Value);
};

// UnkType_10c1e870::Unk_10c1e870
int UnkType_10c1e870::Unk_10c1e870(void* Key, int Value)
{
    int i;
    for ( i = 0; i < unk_38; i++ )
    {
        if ( unk_34[i].unk_0 == Key && Value == unk_34[i].unk_8 )
        {
            return 1;
        }
    }
    for ( i = 0; i < unk_44; i++ )
    {
        if ( unk_40[i].unk_0 == Key && Value == unk_40[i].unk_8 )
        {
            return 1;
        }
    }
    return 0;
}
