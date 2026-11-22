// campaign_leaf_543430.cpp -- one function at file offset 0x543430, preferred VA 0x10e43430. It
// searches the six-byte entries at 0x20 (count at 0x54) from the last for one whose first two
// halfwords equal Key's and returns a one-byte result saying whether it found one. The class,
// method, structure and member names are invented; the offsets and the bytes are the binary's.

struct UnkType_10e43430_Result
{
    UnkType_10e43430_Result(unsigned char Value)
    {
        unk_0 = Value;
    }

    unsigned char unk_0;
};

struct UnkType_10e43430_Entry
{
    unsigned short unk_0;
    unsigned short unk_2;
    unsigned short unk_4;
};

class UnkType_10e43430
{
public:
    UnkType_10e43430_Result Unk_10e43430(const UnkType_10e43430_Entry& Key) const;

    unsigned char unk_0[0x20];
    UnkType_10e43430_Entry unk_20[6];
    unsigned char unk_44[0x10];
    int unk_54;
};

// UnkType_10e43430::Unk_10e43430
UnkType_10e43430_Result UnkType_10e43430::Unk_10e43430(const UnkType_10e43430_Entry& Key) const
{
    int Index;

    for ( Index = unk_54 - 1; Index >= 0; Index-- )
    {
        if ( unk_20[Index].unk_0 == Key.unk_0 && unk_20[Index].unk_2 == Key.unk_2 )
        {
            return UnkType_10e43430_Result(1);
        }
    }
    return UnkType_10e43430_Result(0);
}
