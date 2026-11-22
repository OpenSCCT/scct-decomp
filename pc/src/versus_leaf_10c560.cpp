// versus_leaf_10c560.cpp -- the function at file offset 0x10c560, VA 0x10a0c560, 10 bytes. It returns
// bit 2 of the dword at +0x34 of the object.
// The class and method names are invented; the offset and the bytes come from the binary.

class UnkType_10a0c560
{
public:
    int UnkFunc_10a0c560();

private:
    unsigned char unk_00[0x34];     // not read by this function
    unsigned int unk_34;
};

// UnkType_10a0c560::UnkFunc_10a0c560
int UnkType_10a0c560::UnkFunc_10a0c560()
{
    return (unk_34 >> 2) & 1;
}
