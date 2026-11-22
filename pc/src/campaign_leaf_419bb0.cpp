// campaign_leaf_419bb0.cpp -- one function at file offset 0x419bb0, preferred VA 0x10d19bb0. It
// returns the index of the first three-float entry of the array (data at 0x0, count at 0x4)
// equal to Value, or -1. The class, method, structure and member names are invented; the offsets
// and the bytes are the binary's.

struct UnkType_10d19bb0_Vector
{
    bool operator==(const UnkType_10d19bb0_Vector& Other) const
    {
        return unk_0 == Other.unk_0 && unk_4 == Other.unk_4 && unk_8 == Other.unk_8;
    }

    float unk_0;
    float unk_4;
    float unk_8;
};

class UnkType_10d19bb0
{
public:
    int Unk_10d19bb0(const UnkType_10d19bb0_Vector& Value) const;

    UnkType_10d19bb0_Vector* unk_0;
    int unk_4;
};

// UnkType_10d19bb0::Unk_10d19bb0
int UnkType_10d19bb0::Unk_10d19bb0(const UnkType_10d19bb0_Vector& Value) const
{
    int Index;

    for ( Index = 0; Index < unk_4; Index++ )
    {
        if ( unk_0[Index] == Value )
        {
            return Index;
        }
    }
    return -1;
}
