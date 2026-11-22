// campaign_leaf_57bfd0.cpp -- one function at file offset 0x57bfd0, preferred VA 0x10e7bfd0.
// When both masks are zero it clears the byte at offset 0x18. Otherwise, for each bit i set in
// MaskA it clears the bits of MaskB in the i-th of the 32 ints at offset 0x1c, and for each bit
// set in MaskB the bits of MaskA. The class, method and member names are invented; the offset and
// the bytes are the binary's.

class UnkType_10e7bfd0
{
public:
    unsigned char unk_0[0x18];
    unsigned char unk_18;
    unsigned char unk_19[3];
    unsigned int unk_1c[32];

    void Unk_10e7bfd0(unsigned int MaskA, unsigned int MaskB);
};

// UnkType_10e7bfd0::Unk_10e7bfd0
void UnkType_10e7bfd0::Unk_10e7bfd0(unsigned int MaskA, unsigned int MaskB)
{
    int i;

    if ( MaskA == 0 && MaskB == 0 )
    {
        unk_18 = 0;
        return;
    }
    for ( i = 0; i < 32; i++ )
    {
        if ( MaskA & ( 1 << i ) )
        {
            unk_1c[i] &= ~MaskB;
        }
        if ( MaskB & ( 1 << i ) )
        {
            unk_1c[i] &= ~MaskA;
        }
    }
}
