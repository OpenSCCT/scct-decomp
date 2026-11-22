// campaign_leaf_043610.cpp -- one function at file offset 0x43610, preferred VA 0x10943610. It
// returns true when the box formed by the six floats of this object overlaps the box formed by the
// six floats of another object, taking the minimum words at offsets 0, 4 and 8 and the maximum
// words at 0xc, 0x10 and 0x14, and false otherwise. The class and method names are invented; the
// offset and the bytes are the binary's.

class UnkType_10943610
{
public:
    bool UnkOverlaps(const UnkType_10943610 *Other) const;

private:
    float unk_00;
    float unk_04;
    float unk_08;
    float unk_0c;
    float unk_10;
    float unk_14;
};

// UnkType_10943610::UnkOverlaps
bool UnkType_10943610::UnkOverlaps(const UnkType_10943610 *Other) const
{
    if ( unk_00 > Other->unk_0c || Other->unk_00 > unk_0c
      || unk_04 > Other->unk_10 || Other->unk_04 > unk_10
      || unk_08 > Other->unk_14 || Other->unk_08 > unk_14 )
    {
        return false;
    }
    return true;
}
