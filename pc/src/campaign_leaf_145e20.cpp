// campaign_leaf_145e20.cpp -- returns the byte that the array of pointers at offset 0x00 of this
// holds at Index, or -1 when Index is past the count at offset 0x04. File offset 0x145e20, VA
// 0x10a45e20. The class and method names are invented; the offsets are the binary's, and the
// element types are guesses.

class UnkType_10a45e20
{
public:
    char UnkMethod_10a45e20(int Index);

private:
    char **unk_00;                  // guess: array of pointers to bytes
    int unk_04;                     // count of entries
};

// UnkType_10a45e20::UnkMethod_10a45e20
char UnkType_10a45e20::UnkMethod_10a45e20(int Index)
{
    if ( Index > unk_04 - 1 )
    {
        return -1;
    }
    return *unk_00[Index];
}
