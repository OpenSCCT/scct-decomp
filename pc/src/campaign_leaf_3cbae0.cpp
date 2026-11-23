// campaign_leaf_3cbae0.cpp -- one function at file offset 0x3cbae0, preferred VA 0x10ccbae0. It
// returns 1 when Param occurs in Stream, past its first character, right after a '-' or '/'
// (searching with the function at 0x10ccb5a0), and 0 otherwise or when Stream is empty. The
// function and parameter names are invented; the offsets and the bytes are the binary's.

const unsigned short* Unk_10ccb5a0(const unsigned short* Text, const unsigned short* Find);

// Unk_10ccbae0
int Unk_10ccbae0(const unsigned short* Stream, const unsigned short* Param)
{
    const unsigned short* Found;

    if ( *Stream != 0 )
    {
        for ( Found = Unk_10ccb5a0(Stream + 1, Param); Found != 0;
              Found = Unk_10ccb5a0(Found + 1, Param) )
        {
            if ( Found > Stream && (Found[-1] == '-' || Found[-1] == '/') )
            {
                return 1;
            }
        }
    }
    return 0;
}
