// campaign_leaf_0962b0.cpp -- one function at file offset 0x962b0, preferred VA 0x109962b0. It
// returns the float at offset 0x2dc, or the larger of it and the float at offset 0x2e0 when the
// byte at offset 0x2fc is at least 2. The class, method and member names are invented; the offset
// and the bytes are the binary's.

template<class T> inline T Max(const T A, const T B)
{
    return ( A >= B ) ? A : B;
}

class UnkType_109962b0
{
public:
    unsigned char unk_0[0x2dc];
    float unk_2dc;
    float unk_2e0;
    unsigned char unk_2e4[0x2fc - 0x2e4];
    unsigned char unk_2fc;

    float Unk_109962b0();
};

// UnkType_109962b0::Unk_109962b0
float UnkType_109962b0::Unk_109962b0()
{
    if ( unk_2fc >= 2 )
    {
        return Max(unk_2dc, unk_2e0);
    }
    return unk_2dc;
}
