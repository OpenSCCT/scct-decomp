// campaign_leaf_032510.cpp -- one function at file offset 0x32510, preferred VA 0x10932510. It
// reads the low 16 bits of each of three words of this object as signed values, stores the three
// results in the three words of its argument, and returns that argument. The class, method and
// parameter names are invented; the offset and the bytes are the binary's.

class UnkType_10932510
{
public:
    int *UnkUnpack(int *Out) const;

private:
    int unk_00;                     // low 16 bits read as a signed value
    int unk_04;                     // low 16 bits read as a signed value
    int unk_08;                     // low 16 bits read as a signed value
};

// UnkType_10932510::UnkUnpack
int *UnkType_10932510::UnkUnpack(int *Out) const
{
    int Word2 = unk_08 & 0xffff;
    if ( Word2 > 0x7fff )
    {
        Word2 -= 0x10000;
    }
    int Word1 = unk_04 & 0xffff;
    if ( Word1 > 0x7fff )
    {
        Word1 -= 0x10000;
    }
    int Word0 = unk_00 & 0xffff;
    if ( Word0 > 0x7fff )
    {
        Word0 -= 0x10000;
    }
    Out[1] = Word1;
    Out[0] = Word0;
    Out[2] = Word2;
    return Out;
}
