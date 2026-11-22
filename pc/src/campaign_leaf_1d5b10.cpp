// campaign_leaf_1d5b10.cpp -- one function at file offset 0x1d5b10, preferred VA 0x10ad5b10. It
// returns 1 when an entry of the pointer array at offset 0x48 (count at 0x4c) points to a first
// word equal to its argument, else 0. The class, method and member names are invented; the offset
// and the bytes are the binary's.

class UnkType_10ad5b10
{
public:
    unsigned char unk_0[0x48];
    int** unk_48;
    int unk_4c;

    int Unk_10ad5b10(int Key);
};

// UnkType_10ad5b10::Unk_10ad5b10
int UnkType_10ad5b10::Unk_10ad5b10(int Key)
{
    bool Found = false;
    for ( int i = 0; i < unk_4c && !Found; i++ )
    {
        if ( *unk_48[i] == Key )
        {
            Found = true;
        }
    }
    return Found == true;
}
