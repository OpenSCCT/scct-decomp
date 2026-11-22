// campaign_leaf_5528c0.cpp -- one function at file offset 0x5528c0, preferred VA 0x10e528c0.
// It finds Value in the int array at offset 0xb4 (count at offset 0xb8) and stores 0 in that slot;
// when Value is absent the index is -1 and the store goes to the slot before the array. The
// class, method and member names are invented; the offset and the bytes are the binary's.

class UnkType_10e528c0
{
public:
    unsigned char unk_0[0xb4];
    int* unk_b4;
    int unk_b8;

    int FindIndex(int Value) const
    {
        int i;

        for ( i = 0; i < unk_b8; i++ )
        {
            if ( unk_b4[i] == Value )
            {
                return i;
            }
        }
        return -1;
    }

    void Unk_10e528c0(int Value);
};

// UnkType_10e528c0::Unk_10e528c0
void UnkType_10e528c0::Unk_10e528c0(int Value)
{
    unk_b4[FindIndex(Value)] = 0;
}
