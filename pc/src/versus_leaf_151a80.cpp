// versus_leaf_151a80.cpp -- returns the inline buffer or the pointer at 4, chosen by the int at 0x18 (16 or more selects the pointer), at file offset 0x151a80 (VA 0x10a51a80).
// The class, member, element and method names are invented; the offsets, the element
// strides and the argument sizes are the binary's.

union UnkStorage_10a51a80
{
    char buf[0x10];                     // used while the int at 0x18 is below 0x10
    char *ptr;                          // used when the int at 0x18 is 0x10 or more
};

class UnkType_10a51a80
{
public:
    char *GetUnk04();

private:
    unsigned char unk_00[0x4];          // not read by this function
    UnkStorage_10a51a80 unk_04;
    unsigned char unk_14[0x18 - 0x14];  // not read by this function
    unsigned int unk_18;                // selects the storage
};

// UnkType_10a51a80::GetUnk04
char *UnkType_10a51a80::GetUnk04()
{
    if ( unk_18 >= 0x10 )
        return unk_04.ptr;
    return unk_04.buf;
}
