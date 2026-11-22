// campaign_leaf_2d89c0.cpp -- one function at file offset 0x2d89c0, preferred VA 0x10bd89c0. It
// finds which of the two 0x58-byte entries at offset 0x320 holds its first argument in its first
// word and stores there its 12-byte by-value second argument at entry offset 0x4 and its last two
// arguments at entry offsets 0x10 and 0x3c. The class, method and member names are invented; the
// offset and the bytes are the binary's.

struct UnkType_10bd89c0_Triple
{
    int unk_0;
    int unk_4;
    int unk_8;
};

struct UnkType_10bd89c0_Entry
{
    void* unk_0;
    UnkType_10bd89c0_Triple unk_4;
    int unk_10;
    unsigned char unk_14[0x3c - 0x14];
    int unk_3c;
    unsigned char unk_40[0x58 - 0x40];
};

class UnkType_10bd89c0
{
public:
    unsigned char unk_0[0x320];
    UnkType_10bd89c0_Entry unk_320[2];

    void Unk_10bd89c0(void* Key, UnkType_10bd89c0_Triple Value, int Third, int Fourth);
};

// UnkType_10bd89c0::Unk_10bd89c0
void UnkType_10bd89c0::Unk_10bd89c0(void* Key, UnkType_10bd89c0_Triple Value, int Third, int Fourth)
{
    for ( int i = 0; i < 2; i++ )
    {
        if ( unk_320[i].unk_0 == Key )
        {
            unk_320[i].unk_4 = Value;
            unk_320[i].unk_10 = Third;
            unk_320[i].unk_3c = Fourth;
            return;
        }
    }
}
