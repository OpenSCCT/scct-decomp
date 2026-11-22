// campaign_leaf_35c8b0.cpp -- one function at file offset 0x35c8b0, preferred VA 0x10c5c8b0. It
// returns 1 when the byte at 0x43c is 1 and Value is among the words of the array at 0xc8 (data
// pointer, then count at 0xcc). The class, method, structure and member names are invented; the
// offsets and the bytes are the binary's.

struct UnkArray
{
    int FindItem(int Value) const
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

    int* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10c5c8b0
{
public:
    int Unk_10c5c8b0(int Value) const;

    unsigned char unk_0[0xc8];
    UnkArray unk_c8;
    unsigned char unk_d4[0x368];
    unsigned char unk_43c;
};

// UnkType_10c5c8b0::Unk_10c5c8b0
int UnkType_10c5c8b0::Unk_10c5c8b0(int Value) const
{
    if ( unk_43c == 1 && unk_c8.FindItem(Value) != -1 )
    {
        return 1;
    }
    return 0;
}
