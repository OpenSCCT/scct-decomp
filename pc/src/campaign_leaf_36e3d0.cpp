// campaign_leaf_36e3d0.cpp -- one function at file offset 0x36e3d0, preferred VA 0x10c6e3d0. It
// returns the pointer at 0x2b4 when it is set and one of the flag tests holds: bit 0x20000 of
// Flags with the byte at 0x230 set, bit 0x400000 with the byte at 0x234, or bit 0x80000 with the
// byte at 0x233; otherwise null. Its first and third parameters are unused. The class, method,
// structure, member and parameter names are invented; the offsets and the bytes are the binary's.

struct UnkObject;

class UnkType_10c6e3d0
{
public:
    UnkObject* Unk_10c6e3d0(int, unsigned int Flags, int) const;

    unsigned char unk_0[0x230];
    unsigned char unk_230;
    unsigned char unk_231[2];
    unsigned char unk_233;
    unsigned char unk_234;
    unsigned char unk_235[0x7f];
    UnkObject* unk_2b4;
};

// UnkType_10c6e3d0::Unk_10c6e3d0
UnkObject* UnkType_10c6e3d0::Unk_10c6e3d0(int, unsigned int Flags, int) const
{
    if ( unk_2b4 != 0 )
    {
        if ( ( Flags & 0x20000 ) && unk_230 != 0 )
        {
            return unk_2b4;
        }
        if ( ( Flags & 0x400000 ) && unk_234 != 0 )
        {
            return unk_2b4;
        }
        if ( ( Flags & 0x80000 ) && unk_233 != 0 )
        {
            return unk_2b4;
        }
    }
    return 0;
}
