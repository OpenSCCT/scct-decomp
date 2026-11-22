// campaign_leaf_506880.cpp -- one function at file offset 0x506880, preferred VA 0x10e06880. It
// returns a one-byte result: 0 when First and Second share their high halfwords and First's is
// nonzero, otherwise whether bit (Second & 31) is set in the word at 0x1c + 4 * (First & 31).
// The class, method, structure, member and parameter names are invented; the offsets and the
// bytes are the binary's.

struct UnkResult
{
    UnkResult(unsigned char Value)
    {
        unk_0 = Value;
    }

    unsigned char unk_0;
};

class UnkType_10e06880
{
public:
    UnkResult Unk_10e06880(unsigned int First, unsigned int Second) const;

    unsigned char unk_0[0x1c];
    unsigned int unk_1c[32];
};

// UnkType_10e06880::Unk_10e06880
UnkResult UnkType_10e06880::Unk_10e06880(unsigned int First, unsigned int Second) const
{
    if ( ( ( First ^ Second ) & 0xffff0000 ) == 0 && ( First & 0xffff0000 ) != 0 )
    {
        return UnkResult(0);
    }
    return UnkResult(( unk_1c[First & 0x1f] & ( 1 << ( Second & 0x1f ) ) ) != 0);
}
