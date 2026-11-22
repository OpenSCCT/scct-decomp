// campaign_leaf_4ef010.cpp -- one function at file offset 0x4ef010, preferred VA 0x10def010. It
// folds a new sample into two running averages: the first call (word at 0x8 is -1) seeds the
// word at 0x0 with eight times the sample; later calls move it by the sample's difference from
// its eighth and move the word at 0x4 by a quarter towards that difference's magnitude. The
// sample is kept at 0x8. The class, method, member and parameter names are invented; the offsets
// and the bytes are the binary's.

class UnkType_10def010
{
public:
    void Unk_10def010(int Sample);

    unsigned int unk_0;
    unsigned int unk_4;
    int unk_8;
};

// UnkType_10def010::Unk_10def010
// guess: a smoothed round-trip time and its mean deviation, as TCP keeps them.
void UnkType_10def010::Unk_10def010(int Sample)
{
    int Delta;

    if ( unk_8 == -1 )
    {
        unk_0 = Sample * 8;
        unk_8 = Sample;
        return;
    }
    Delta = Sample - ( unk_0 >> 3 );
    unk_0 += Delta;
    if ( Delta < 0 )
    {
        Delta = -Delta;
    }
    unk_4 = unk_4 - ( unk_4 >> 2 ) + Delta;
    unk_8 = Sample;
}
