// campaign_leaf_346260.cpp -- one function at file offset 0x346260, preferred VA 0x10c46260. It
// returns 0 when the byte array at offset 0x444 (count at 0x448) contains the word its argument
// points to, else 1. The class, method and member names are invented; the offset and the bytes are
// the binary's.

class UnkType_10c46260
{
public:
    unsigned char unk_0[0x444];
    unsigned char* unk_444;
    int unk_448;

    int Unk_10c46260(const int& Value);
};

// UnkType_10c46260::Unk_10c46260
int UnkType_10c46260::Unk_10c46260(const int& Value)
{
    for ( int i = 0; i < unk_448; i++ )
    {
        if ( unk_444[i] == Value )
        {
            return 0;
        }
    }
    return 1;
}
