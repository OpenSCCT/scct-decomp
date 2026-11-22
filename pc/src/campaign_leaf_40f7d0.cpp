// campaign_leaf_40f7d0.cpp -- one function at file offset 0x40f7d0, preferred VA 0x10d0f7d0. It
// returns 1 when the pointer array at 0x2c (count at 0x30) holds an entry with word Key at 0x4
// and kind 2 or 6 in its byte at 0x18, or the pointer array at 0x38 (count at 0x3c) holds one
// with word Key at 0x4 and kind 2 or 6 in its byte at 0x8. The class, method, structure, member
// and parameter names are invented; the offsets and the bytes are the binary's.

struct UnkType_10d0f7d0_First
{
    int unk_0;
    int unk_4;
    unsigned char unk_8[0x10];
    unsigned char unk_18;
};

struct UnkType_10d0f7d0_Second
{
    int unk_0;
    int unk_4;
    unsigned char unk_8;
};

class UnkType_10d0f7d0
{
public:
    int Unk_10d0f7d0(int Key) const;

    unsigned char unk_0[0x2c];
    UnkType_10d0f7d0_First** unk_2c;
    int unk_30;
    int unk_34;
    UnkType_10d0f7d0_Second** unk_38;
    int unk_3c;
};

// UnkType_10d0f7d0::Unk_10d0f7d0
int UnkType_10d0f7d0::Unk_10d0f7d0(int Key) const
{
    int Index;

    for ( Index = 0; Index < unk_30; Index++ )
    {
        if ( unk_2c[Index]->unk_4 == Key
            && (unk_2c[Index]->unk_18 == 2 || unk_2c[Index]->unk_18 == 6) )
        {
            return 1;
        }
    }
    for ( Index = 0; Index < unk_3c; Index++ )
    {
        if ( unk_38[Index]->unk_4 == Key
            && (unk_38[Index]->unk_8 == 2 || unk_38[Index]->unk_8 == 6) )
        {
            return 1;
        }
    }
    return 0;
}
