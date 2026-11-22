// campaign_leaf_18a540.cpp -- one function at file offset 0x18a540, preferred VA 0x10a8a540. It
// returns 1 when the float at offset 0x224 equals the one at 0x320 and is below the one at 0x328,
// or the float at offset 0x220 equals the one at 0x324 and is below the one at 0x32c; otherwise 0.
// The class, method and member names are invented; the offset and the bytes are the binary's.

class UnkType_10a8a540
{
public:
    unsigned char unk_0[0x220];
    float unk_220;
    float unk_224;
    unsigned char unk_228[0x320 - 0x228];
    float unk_320;
    float unk_324;
    float unk_328;
    float unk_32c;

    int Unk_10a8a540();
};

// UnkType_10a8a540::Unk_10a8a540
int UnkType_10a8a540::Unk_10a8a540()
{
    if ( ( unk_224 == unk_320 && unk_224 < unk_328 )
        || ( unk_220 == unk_324 && unk_220 < unk_32c ) )
    {
        return 1;
    }
    return 0;
}
