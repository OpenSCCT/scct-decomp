// campaign_leaf_321850.cpp -- one function at file offset 0x321850, preferred VA 0x10c21850. It
// returns the index of the first byte equal to its argument in the byte array at offset 0x58 (count
// at offset 0x74), or -1. The class, method and member names are invented; the offset and the bytes
// are the binary's.

class UnkType_10c21850
{
public:
    unsigned char unk_0[0x58];
    unsigned char* unk_58;
    unsigned char unk_5c[0x74 - 0x5c];
    int unk_74;

    int Unk_10c21850(int Value);
};

// UnkType_10c21850::Unk_10c21850
int UnkType_10c21850::Unk_10c21850(int Value)
{
    int Result = -1;
    for ( int i = 0; i < unk_74; i++ )
    {
        if ( unk_58[i] == Value )
        {
            Result = i;
            break;
        }
    }
    return Result;
}
