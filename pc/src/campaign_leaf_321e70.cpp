// campaign_leaf_321e70.cpp -- one function at file offset 0x321e70, preferred VA 0x10c21e70. It
// returns 1 when the byte array at offset 0x58 (count at 0x74) contains its argument, else 0, by
// way of the index search at VA 0x10c21850. The class, method and member names are invented; the
// offset and the bytes are the binary's.

class UnkType_10c21e70
{
public:
    unsigned char unk_0[0x58];
    unsigned char* unk_58;
    unsigned char unk_5c[0x74 - 0x5c];
    int unk_74;

    // the function at VA 0x10c21850
    int Unk_10c21850(int Value)
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

    int Unk_10c21e70(int Value);
};

// UnkType_10c21e70::Unk_10c21e70
int UnkType_10c21e70::Unk_10c21e70(int Value)
{
    return Unk_10c21850(Value) >= 0;
}
