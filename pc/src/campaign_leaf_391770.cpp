// campaign_leaf_391770.cpp -- one function at file offset 0x391770, preferred VA 0x10c91770. It
// searches the twelve-byte entries at 0x28 (count at 0x2c) for one whose first byte equals Key
// and returns it; failing that it returns the last entry whose first byte is 0, or the first
// entry. The class, method, structure and member names are invented; the offsets and the bytes
// are the binary's.

struct UnkType_10c91770_Entry
{
    unsigned char unk_0;
    unsigned char unk_1[0xb];
};

class UnkType_10c91770
{
public:
    UnkType_10c91770_Entry* Unk_10c91770(int Key) const;

    unsigned char unk_0[0x28];
    UnkType_10c91770_Entry* unk_28;
    int unk_2c;
};

// UnkType_10c91770::Unk_10c91770
UnkType_10c91770_Entry* UnkType_10c91770::Unk_10c91770(int Key) const
{
    UnkType_10c91770_Entry* Free = unk_28;
    int Index;

    for ( Index = 0; Index < unk_2c; Index++ )
    {
        if ( unk_28[Index].unk_0 == Key )
        {
            return &unk_28[Index];
        }
        if ( unk_28[Index].unk_0 == 0 )
        {
            Free = &unk_28[Index];
        }
    }
    return Free;
}
