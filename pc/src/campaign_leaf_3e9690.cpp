// campaign_leaf_3e9690.cpp -- one function at file offset 0x3e9690, preferred VA 0x10ce9690. It
// copies as many words from Source to Dest as the halfword at 0x34 says, a single word by one
// store. Its third parameter is unused. The class, method, member and parameter names are
// invented; the offsets and the bytes are the binary's.

class UnkType_10ce9690
{
public:
    void Unk_10ce9690(int* Dest, const int* Source, int) const;

    unsigned char unk_0[0x34];
    unsigned short unk_34;
};

// UnkType_10ce9690::Unk_10ce9690
void UnkType_10ce9690::Unk_10ce9690(int* Dest, const int* Source, int) const
{
    int Index;

    if ( unk_34 == 1 )
    {
        *Dest = *Source;
    }
    else
    {
        for ( Index = 0; Index < unk_34; Index++ )
        {
            Dest[Index] = Source[Index];
        }
    }
}
