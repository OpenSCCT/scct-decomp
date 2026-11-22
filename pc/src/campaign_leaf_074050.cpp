// campaign_leaf_074050.cpp -- one function at file offset 0x74050, preferred VA 0x10974050. It
// copies the seven words at offset 0x6c of this object to the block its first argument points to,
// and returns that block. Its second argument is not used. The class, struct, method and parameter
// names are invented; the offset and the bytes are the binary's.

struct UnkType_10974050_Block
{
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
    int unk_10;
    int unk_14;
    int unk_18;
};

class UnkType_10974050
{
public:
    UnkType_10974050_Block *UnkCopyBlock(UnkType_10974050_Block *Out, int Unused) const;

private:
    unsigned char unk_00[0x6c];     // not read by this function
    UnkType_10974050_Block unk_6c;
};

// UnkType_10974050::UnkCopyBlock
UnkType_10974050_Block *
UnkType_10974050::UnkCopyBlock(UnkType_10974050_Block *Out, int Unused) const
{
    *Out = unk_6c;
    return Out;
}
