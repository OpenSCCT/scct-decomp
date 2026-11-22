// campaign_leaf_1e9990.cpp -- one function at file offset 0x1e9990, preferred VA 0x10ae9990. It
// returns the index of the 8-byte entry whose first word equals its first argument in the array at
// offset 0x7c (count at 0x80) when its second argument (a byte) is zero, or in the array at offset
// 0x88 (count at 0x8c) otherwise; -1 when there is none. The class, method and member names are
// invented; the offset and the bytes are the binary's.

struct UnkType_10ae9990_Pair
{
    int unk_0;
    int unk_4;
};

class UnkType_10ae9990
{
public:
    unsigned char unk_0[0x7c];
    UnkType_10ae9990_Pair* unk_7c;
    int unk_80;
    unsigned char unk_84[0x88 - 0x84];
    UnkType_10ae9990_Pair* unk_88;
    int unk_8c;

    int Unk_10ae9990(int Key, unsigned char Second);
};

// UnkType_10ae9990::Unk_10ae9990
int UnkType_10ae9990::Unk_10ae9990(int Key, unsigned char Second)
{
    int i;
    if ( !Second )
    {
        for ( i = 0; i < unk_80; i++ )
        {
            if ( unk_7c[i].unk_0 == Key )
            {
                return i;
            }
        }
        return -1;
    }
    for ( i = 0; i < unk_8c; i++ )
    {
        if ( unk_88[i].unk_0 == Key )
        {
            return i;
        }
    }
    return -1;
}
