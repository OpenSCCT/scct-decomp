// campaign_leaf_5069f0.cpp -- one function at file offset 0x5069f0, preferred VA 0x10e069f0. For
// each of 32 bits it clears the bits of Second in the word at 0x1c + 4 * bit when First has that
// bit, and the bits of First when Second has it. The class, method, member and parameter names
// are invented; the offsets and the bytes are the binary's.

class UnkType_10e069f0
{
public:
    void Unk_10e069f0(unsigned int First, unsigned int Second);

    unsigned char unk_0[0x1c];
    unsigned int unk_1c[32];
};

// UnkType_10e069f0::Unk_10e069f0
void UnkType_10e069f0::Unk_10e069f0(unsigned int First, unsigned int Second)
{
    int Index;

    for ( Index = 0; Index < 32; Index++ )
    {
        unsigned int Bit = 1 << Index;

        if ( First & Bit )
        {
            unk_1c[Index] &= ~Second;
        }
        if ( Second & Bit )
        {
            unk_1c[Index] &= ~First;
        }
    }
}
