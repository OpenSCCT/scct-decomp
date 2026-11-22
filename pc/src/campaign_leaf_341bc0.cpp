// campaign_leaf_341bc0.cpp -- one function at file offset 0x341bc0, preferred VA 0x10c41bc0. It
// searches the four key-value pairs at offset 0x414 for its first argument; when found it stores
// the value through its second argument and returns 1, else returns 0. The class, method and member
// names are invented; the offset and the bytes are the binary's.

struct UnkPair
{
    int unk_0;
    int unk_4;
};

class UnkType_10c41bc0
{
public:
    unsigned char unk_0[0x414];
    UnkPair unk_414[4];

    int Unk_10c41bc0(int Key, int* Out);
};

// UnkType_10c41bc0::Unk_10c41bc0
int UnkType_10c41bc0::Unk_10c41bc0(int Key, int* Out)
{
    for ( int i = 0; i < 4; i++ )
    {
        if ( unk_414[i].unk_0 == Key )
        {
            *Out = unk_414[i].unk_4;
            return 1;
        }
    }
    return 0;
}
