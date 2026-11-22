// campaign_leaf_0af860.cpp -- one function at file offset 0xaf860, preferred VA 0x109af860. It
// returns by value the member-wise sum of the three integers of its object and those of its
// argument. The class, method and member names are invented; the offset and the bytes are the
// binary's.

class UnkIntTriple
{
public:
    int unk_0;
    int unk_4;
    int unk_8;

    UnkIntTriple(int First, int Second, int Third)
        : unk_0(First), unk_4(Second), unk_8(Third)
    {
    }

    UnkIntTriple Unk_109af860(const UnkIntTriple& Other) const;
};

// UnkIntTriple::Unk_109af860
UnkIntTriple UnkIntTriple::Unk_109af860(const UnkIntTriple& Other) const
{
    return UnkIntTriple(unk_0 + Other.unk_0, unk_4 + Other.unk_4, unk_8 + Other.unk_8);
}
