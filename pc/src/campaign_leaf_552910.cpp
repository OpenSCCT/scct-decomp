// campaign_leaf_552910.cpp -- one function at file offset 0x552910, preferred VA 0x10e52910. It
// finds Value in the int array at offset 0x6c (count at offset 0x70) and stores 0 in that slot;
// when Value is absent the index is -1 and the store goes to the slot before the array. The
// class, method and member names are invented; the offset and the bytes are the binary's.

class UnkType_10e52910
{
public:
    unsigned char unk_0[0x6c];
    int* unk_6c;
    int unk_70;

    int FindIndex(int Value) const
    {
        int i;

        for ( i = 0; i < unk_70; i++ )
        {
            if ( unk_6c[i] == Value )
            {
                return i;
            }
        }
        return -1;
    }

    void Unk_10e52910(int Value);
};

// UnkType_10e52910::Unk_10e52910
void UnkType_10e52910::Unk_10e52910(int Value)
{
    unk_6c[FindIndex(Value)] = 0;
}
