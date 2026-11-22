// campaign_leaf_145b50.cpp -- returns the dword at offset 0x04 of the first entry in the array at
// offset 0x00 of this whose first byte equals the argument, or 0 when none does. File offset
// 0x145b50, VA 0x10a45b50. The class and method names are invented; the offsets are the binary's,
// and the entry type is a guess.

class UnkEntry_10a45b50;

class UnkType_10a45b50
{
public:
    int UnkMethod_10a45b50(unsigned char Key);

private:
    UnkEntry_10a45b50 **unk_00;     // guess: array of pointers to entries
    int unk_04;                     // count of entries
};

class UnkEntry_10a45b50
{
public:
    unsigned char unk_00;
    unsigned char unk_01[3];        // not read by this function
    int unk_04;
};

// UnkType_10a45b50::UnkMethod_10a45b50
int UnkType_10a45b50::UnkMethod_10a45b50(unsigned char Key)
{
    int i;

    for ( i = 0; i < unk_04; i++ )
    {
        if ( unk_00[i]->unk_00 == Key )
        {
            return unk_00[i]->unk_04;
        }
    }
    return 0;
}
