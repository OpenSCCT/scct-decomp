// campaign_leaf_194a80.cpp -- returns the index of the first dword of the array at offset 0x28 of
// this that equals the argument, among the count at offset 0x2c, or -1. File offset 0x194a80, VA
// 0x10a94a80. The class and method names are invented; the offsets are the binary's.

class UnkType_10a94a80
{
public:
    int UnkMethod_10a94a80(int Value);

private:
    unsigned char unk_00[0x28];     // not read by this function
    int *unk_28;                    // guess: array of dwords
    int unk_2c;                     // count of entries
};

// UnkType_10a94a80::UnkMethod_10a94a80
int UnkType_10a94a80::UnkMethod_10a94a80(int Value)
{
    int i;

    for ( i = 0; i < unk_2c; i++ )
    {
        if ( unk_28[i] == Value )
        {
            return i;
        }
    }
    return -1;
}
