// campaign_leaf_158b90.cpp -- stores the second argument at offset 0x24 of the entry at the first
// argument's index in each of the two arrays at offsets 0x68 and 0x74 of this, where it differs.
// File offset 0x158b90, VA 0x10a58b90. The class and method names are invented; the offsets are the
// binary's, and the entry type is a guess.

class UnkEntry_10a58b90;

class UnkType_10a58b90
{
public:
    void UnkMethod_10a58b90(int Index, int Value);

private:
    unsigned char unk_00[0x68];     // not read by this function
    UnkEntry_10a58b90 *unk_68;      // guess: array of entries
    unsigned char unk_6c[8];        // not read by this function
    UnkEntry_10a58b90 *unk_74;      // guess: array of entries
};

class UnkEntry_10a58b90
{
public:
    unsigned char unk_00[0x24];     // not read by this function
    int unk_24;
    unsigned char unk_28[0x14];     // not read by this function
};

// UnkType_10a58b90::UnkMethod_10a58b90
void UnkType_10a58b90::UnkMethod_10a58b90(int Index, int Value)
{
    if ( unk_68[Index].unk_24 != Value )
    {
        unk_68[Index].unk_24 = Value;
    }
    if ( unk_74[Index].unk_24 != Value )
    {
        unk_74[Index].unk_24 = Value;
    }
}
