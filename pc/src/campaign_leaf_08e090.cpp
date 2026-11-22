// campaign_leaf_08e090.cpp -- one function at file offset 0x8e090, preferred VA 0x1098e090. It
// copies the three words at offset 0xe8 of this object to the block its first argument points to,
// and returns that block. Its second argument is not used. The class, struct, method and parameter
// names are invented; the offset and the bytes are the binary's.

struct UnkType_1098e090_Triple
{
    int unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_1098e090
{
public:
    UnkType_1098e090_Triple *UnkCopyTriple(UnkType_1098e090_Triple *Out, int Unused) const;

private:
    unsigned char unk_00[0xe8];     // not read by this function
    UnkType_1098e090_Triple unk_e8;
};

// UnkType_1098e090::UnkCopyTriple
UnkType_1098e090_Triple *
UnkType_1098e090::UnkCopyTriple(UnkType_1098e090_Triple *Out, int Unused) const
{
    *Out = unk_e8;
    return Out;
}
