// campaign_leaf_538770.cpp -- thiscall method at VA 0x10e38770: ORs the mask word of the second
// index into that of the first (words at 0x10c), then repeats for every pair in the array at 0x4d90
// (count at 0x4d94) whose second member is the first index, one level deeper. guess: propagates a
// set of flags along links. All names are invented.

struct UnkType_10e38770_Link
{
    int unk_00;
    int unk_04;
};

class UnkType_10e38770
{
public:
    void Unk_10e38770(int Target, int Source, int Depth);

private:
    int unk_00[0x10c / 4];
    unsigned int unk_10c[(0x4d90 - 0x10c) / 4];
    UnkType_10e38770_Link* unk_4d90;
    int unk_4d94;
};

// UnkType_10e38770::Unk_10e38770
void UnkType_10e38770::Unk_10e38770(int Target, int Source, int Depth)
{
    unk_10c[Target] |= unk_10c[Source];
    for ( int Index = 0; Index < unk_4d94; Index++ )
    {
        UnkType_10e38770_Link& Link = unk_4d90[Index];
        if ( Link.unk_04 == Target )
        {
            Unk_10e38770(Link.unk_00, Link.unk_04, Depth + 1);
        }
    }
}
