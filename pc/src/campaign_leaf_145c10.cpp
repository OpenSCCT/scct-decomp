// campaign_leaf_145c10.cpp -- returns the dword at offset 0x08 of the first entry in the array at
// offset 0x00 of this whose first byte equals the argument, or 0 when none does. File offset
// 0x145c10, VA 0x10a45c10. The class and method names are invented; the offsets are the binary's,
// and the entry type is a guess.

class UnkEntry_10a45c10;

class UnkType_10a45c10
{
public:
    int UnkMethod_10a45c10(unsigned char Key);

private:
    UnkEntry_10a45c10 **unk_00;     // guess: array of pointers to entries
    int unk_04;                     // count of entries
};

class UnkEntry_10a45c10
{
public:
    unsigned char unk_00;
    unsigned char unk_01[3];        // not read by this function
    int unk_04;
    int unk_08;
};

// UnkType_10a45c10::UnkMethod_10a45c10
int UnkType_10a45c10::UnkMethod_10a45c10(unsigned char Key)
{
    int i;

    for ( i = 0; i < unk_04; i++ )
    {
        if ( unk_00[i]->unk_00 == Key )
        {
            return unk_00[i]->unk_08;
        }
    }
    return 0;
}
