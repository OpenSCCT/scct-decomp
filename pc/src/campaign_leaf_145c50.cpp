// campaign_leaf_145c50.cpp -- returns the dword at offset 0x08 of the first entry in the array at
// offset 0x00 of this whose dword at offset 0x04 equals the argument, or 0 when none does. File
// offset 0x145c50, VA 0x10a45c50. The class and method names are invented; the offsets are the
// binary's, and the entry type is a guess.

class UnkEntry_10a45c50;

class UnkType_10a45c50
{
public:
    int UnkMethod_10a45c50(int Value);

private:
    UnkEntry_10a45c50 **unk_00;     // guess: array of pointers to entries
    int unk_04;                     // count of entries
};

class UnkEntry_10a45c50
{
public:
    unsigned char unk_00[4];        // not read by this function
    int unk_04;
    int unk_08;
};

// UnkType_10a45c50::UnkMethod_10a45c50
int UnkType_10a45c50::UnkMethod_10a45c50(int Value)
{
    int i;

    for ( i = 0; i < unk_04; i++ )
    {
        if ( unk_00[i]->unk_04 == Value )
        {
            return unk_00[i]->unk_08;
        }
    }
    return 0;
}
