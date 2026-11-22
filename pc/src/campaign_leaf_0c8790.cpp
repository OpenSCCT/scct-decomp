// campaign_leaf_0c8790.cpp -- one function at file offset 0xc8790, preferred VA 0x109c8790. It
// returns 1 when the three words of this object equal the three words of its argument, and 0
// otherwise. The class and method names are invented; the offset and the bytes are the binary's.

struct UnkType_109c8790_Triple
{
    int unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109c8790
{
public:
    int UnkEqual(const UnkType_109c8790_Triple *Other) const;

private:
    UnkType_109c8790_Triple unk_00;
};

// UnkType_109c8790::UnkEqual
int UnkType_109c8790::UnkEqual(const UnkType_109c8790_Triple *Other) const
{
    if ( unk_00.unk_00 == Other->unk_00 && unk_00.unk_04 == Other->unk_04
         && unk_00.unk_08 == Other->unk_08 )
    {
        return 1;
    }
    return 0;
}
