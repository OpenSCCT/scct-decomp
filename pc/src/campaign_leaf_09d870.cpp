// campaign_leaf_09d870.cpp -- one function at file offset 0x9d870, preferred VA 0x1099d870. It
// returns the element of the int array at offset 0x28 at the index in its argument, or 0 when the
// index is negative or above the count at offset 0x2c less one. The class and method names are
// invented; the offset and the bytes are the binary's.

class UnkType_1099d870
{
public:
    int UnkGetItemChecked(int Index) const;

private:
    unsigned char unk_00[0x28];     // not read by this function
    int *unk_28;
    int unk_2c;
};

// UnkType_1099d870::UnkGetItemChecked
int UnkType_1099d870::UnkGetItemChecked(int Index) const
{
    if ( Index < 0 || Index > unk_2c - 1 )
    {
        return 0;
    }
    return unk_28[Index];
}
