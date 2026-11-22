// campaign_leaf_145b00.cpp -- returns the dword at offset 0x04 of the entry at Index in the array
// of pointers at offset 0x00 of this, when Index is below the value at offset 0x04, otherwise 0.
// File offset 0x145b00, VA 0x10a45b00. The class and method names are invented; the offsets are the
// binary's, and the entry type is a guess.

class UnkTarget_10a45b00;

class UnkType_10a45b00
{
public:
    int UnkMethod_10a45b00(unsigned char Index);

private:
    UnkTarget_10a45b00 **unk_00;    // guess: array of pointers to entries
    int unk_04;                     // compared with Index
};

class UnkTarget_10a45b00
{
public:
    unsigned char unk_00[4];        // not read by this function
    int unk_04;
};

// UnkType_10a45b00::UnkMethod_10a45b00
int UnkType_10a45b00::UnkMethod_10a45b00(unsigned char Index)
{
    if ( Index < unk_04 )
    {
        return unk_00[Index]->unk_04;
    }
    return 0;
}
