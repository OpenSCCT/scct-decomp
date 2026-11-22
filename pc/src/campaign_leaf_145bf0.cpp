// campaign_leaf_145bf0.cpp -- returns the dword at offset 0x08 of the entry at Index in the array of
// pointers at offset 0x00 of this, when Index is below the value at offset 0x04, otherwise 0. File
// offset 0x145bf0, VA 0x10a45bf0. The class and method names are invented; the offsets are the
// binary's, and the entry type is a guess.

class UnkTarget_10a45bf0;

class UnkType_10a45bf0
{
public:
    int UnkMethod_10a45bf0(unsigned char Index);

private:
    UnkTarget_10a45bf0 **unk_00;    // guess: array of pointers to entries
    int unk_04;                     // compared with Index
};

class UnkTarget_10a45bf0
{
public:
    unsigned char unk_00[8];        // not read by this function
    int unk_08;
};

// UnkType_10a45bf0::UnkMethod_10a45bf0
int UnkType_10a45bf0::UnkMethod_10a45bf0(unsigned char Index)
{
    if ( Index < unk_04 )
    {
        return unk_00[Index]->unk_08;
    }
    return 0;
}
