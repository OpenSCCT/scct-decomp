// campaign_leaf_506930.cpp -- one function at file offset 0x506930, preferred VA 0x10e06930. For
// each of 32 bits it ors Second into the word at 0x1c + 4 * bit when First has that bit, and
// First when Second has it. The class, method, member and parameter names are invented; the
// offsets and the bytes are the binary's.

class UnkType_10e06930
{
public:
    void Unk_10e06930(unsigned int First, unsigned int Second);

    unsigned char unk_0[0x1c];
    unsigned int unk_1c[32];
};

// UnkType_10e06930::Unk_10e06930
void UnkType_10e06930::Unk_10e06930(unsigned int First, unsigned int Second)
{
    int Index;

    for ( Index = 0; Index < 32; Index++ )
    {
        unsigned int Bit = 1 << Index;

        if ( First & Bit )
        {
            unk_1c[Index] |= Second;
        }
        if ( Second & Bit )
        {
            unk_1c[Index] |= First;
        }
    }
}
