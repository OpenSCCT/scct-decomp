// campaign_leaf_072320.cpp -- one function at file offset 0x72320, preferred VA 0x10972320. It
// copies the three words at offset 0xe8 of its second argument into the object its first argument
// points to, and returns the first argument. It does not use this. The class, struct, method and
// parameter names are invented; the offset and the bytes are the binary's.

struct UnkType_10972320_Triple
{
    int unk_00;
    int unk_04;
    int unk_08;
};

struct UnkType_10972320_Source
{
    unsigned char unk_00[0xe8];     // not read by this function
    UnkType_10972320_Triple unk_e8; // copied by this function
};

class UnkType_10972320
{
public:
    UnkType_10972320_Triple *UnkCopyTriple(UnkType_10972320_Triple *Out,
                                           const UnkType_10972320_Source *Source) const;
};

// UnkType_10972320::UnkCopyTriple
UnkType_10972320_Triple *
UnkType_10972320::UnkCopyTriple(UnkType_10972320_Triple *Out,
                                const UnkType_10972320_Source *Source) const
{
    *Out = Source->unk_e8;
    return Out;
}
