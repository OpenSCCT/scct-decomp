// campaign_leaf_765c90.cpp -- one function at file offset 0x765c90, preferred VA 0x11065c90. When
// the word at 0x54 is 7 it copies the words at 0x38 and 0x3c out through its two arguments, and
// otherwise stores zero through both. The class, method and member names are invented; the offset
// and the bytes are the binary's.

class UnkType_11065c90
{
public:
    void Unk_11065c90(int* First, int* Second);

    unsigned char unk_0[0x38];
    int unk_38;
    int unk_3c;
    unsigned char unk_40[0x54 - 0x40];
    int unk_54;
};

// UnkType_11065c90::Unk_11065c90
void UnkType_11065c90::Unk_11065c90(int* First, int* Second)
{
    if ( unk_54 == 7 )
    {
        *First = unk_38;
        *Second = unk_3c;
    }
    else
    {
        *First = 0;
        *Second = 0;
    }
}
