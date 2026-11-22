// campaign_leaf_08fc30.cpp -- one function at file offset 0x8fc30, preferred VA 0x1098fc30. It
// returns the element of the int array at offset 0x1b0 at the index in its argument, or 0 when the
// index is negative or not below the count at offset 0x1b4. The class and method names are
// invented; the offset and the bytes are the binary's.

class UnkType_1098fc30
{
public:
    int UnkGetItem(int Index) const;

private:
    unsigned char unk_00[0x1b0];    // not read by this function
    int *unk_1b0;
    int unk_1b4;
};

// UnkType_1098fc30::UnkGetItem
int UnkType_1098fc30::UnkGetItem(int Index) const
{
    if ( Index < 0 || Index >= unk_1b4 )
    {
        return 0;
    }
    return unk_1b0[Index];
}
