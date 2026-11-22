// campaign_leaf_0c8480.cpp -- one function at file offset 0xc8480, preferred VA 0x109c8480. It
// returns the byte at offset 0x2d of its pointer argument, or 0 for a null pointer. The class and
// method names are invented; the offset and the bytes are the binary's.

struct UnkType_109c8480_Other
{
    unsigned char unk_00[0x2d];     // not read by this function
    unsigned char unk_2d;
};

class UnkType_109c8480
{
public:
    unsigned char UnkGetFlag(const UnkType_109c8480_Other *Other) const;
};

// UnkType_109c8480::UnkGetFlag
unsigned char UnkType_109c8480::UnkGetFlag(const UnkType_109c8480_Other *Other) const
{
    if ( Other != 0 )
    {
        return Other->unk_2d;
    }
    return 0;
}
