// campaign_leaf_3e91c0.cpp -- one function at file offset 0x3e91c0, preferred VA 0x10ce91c0. It
// copies as many words from Source to Dest as the halfword at 0x34 says, a single word by one
// store. Its third parameter is unused. The class, method, member and parameter names are
// invented; the offsets and the bytes are the binary's.

class UnkType_10ce91c0
{
public:
    void Unk_10ce91c0(int* Dest, const int* Source, int) const;

    unsigned char unk_0[0x34];
    unsigned short unk_34;
};

// UnkType_10ce91c0::Unk_10ce91c0
void UnkType_10ce91c0::Unk_10ce91c0(int* Dest, const int* Source, int) const
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
