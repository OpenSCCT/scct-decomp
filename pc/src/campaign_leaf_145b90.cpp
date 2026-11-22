// campaign_leaf_145b90.cpp -- returns the dword at offset 0x04 of the first entry in the array at
// offset 0x00 of this whose dword at offset 0x08 equals the argument, or 0 when none does. File
// offset 0x145b90, VA 0x10a45b90. The class and method names are invented; the offsets are the
// binary's, and the entry type is a guess.

class UnkEntry_10a45b90;

class UnkType_10a45b90
{
public:
    int UnkMethod_10a45b90(int Value);

private:
    UnkEntry_10a45b90 **unk_00;     // guess: array of pointers to entries
    int unk_04;                     // count of entries
};

class UnkEntry_10a45b90
{
public:
    unsigned char unk_00[4];        // not read by this function
    int unk_04;
    int unk_08;
};

// UnkType_10a45b90::UnkMethod_10a45b90
int UnkType_10a45b90::UnkMethod_10a45b90(int Value)
{
    int i;

    for ( i = 0; i < unk_04; i++ )
    {
        if ( unk_00[i]->unk_08 == Value )
        {
            return unk_00[i]->unk_04;
        }
    }
    return 0;
}
