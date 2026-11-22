// campaign_leaf_2d5ef0.cpp -- one function at file offset 0x2d5ef0, preferred VA 0x10bd5ef0. It
// returns 1 when any 0x58-byte entry of the array at offset 0x2b4 (count at 0x2b8) has a non-null
// word in its array at offset 0x24 (count at 0x28), else 0. The class, method and member names are
// invented; the offset and the bytes are the binary's.

struct UnkGroup
{
    unsigned char unk_0[0x24];
    void** unk_24;
    int unk_28;
    unsigned char unk_2c[0x58 - 0x2c];
};

class UnkType_10bd5ef0
{
public:
    unsigned char unk_0[0x2b4];
    UnkGroup* unk_2b4;
    int unk_2b8;

    int Unk_10bd5ef0();
};

// UnkType_10bd5ef0::Unk_10bd5ef0
int UnkType_10bd5ef0::Unk_10bd5ef0()
{
    for ( int i = 0; i < unk_2b8; i++ )
    {
        for ( int j = 0; j < unk_2b4[i].unk_28; j++ )
        {
            if ( unk_2b4[i].unk_24[j] != 0 )
            {
                return 1;
            }
        }
    }
    return 0;
}
