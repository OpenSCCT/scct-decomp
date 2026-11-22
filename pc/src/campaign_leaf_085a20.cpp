// campaign_leaf_085a20.cpp -- one function at file offset 0x85a20, preferred VA 0x10985a20. It
// copies the seven words at offset 0x398 of its second argument to the block its first argument
// points to, and returns that block. It does not use this. The class, struct, method and parameter
// names are invented; the offset and the bytes are the binary's.

struct UnkType_10985a20_Block
{
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
    int unk_10;
    int unk_14;
    int unk_18;
};

struct UnkType_10985a20_Source
{
    unsigned char unk_00[0x398];    // not read by this function
    UnkType_10985a20_Block unk_398;
};

class UnkType_10985a20
{
public:
    UnkType_10985a20_Block *UnkCopyBlock(UnkType_10985a20_Block *Out,
                                         const UnkType_10985a20_Source *Src) const;
};

// UnkType_10985a20::UnkCopyBlock
UnkType_10985a20_Block *
UnkType_10985a20::UnkCopyBlock(UnkType_10985a20_Block *Out,
                               const UnkType_10985a20_Source *Src) const
{
    *Out = Src->unk_398;
    return Out;
}
