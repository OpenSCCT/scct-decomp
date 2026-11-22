// campaign_leaf_1034e0.cpp -- returns 1 when the dword at offset 0x34 of this is not above the first
// argument, the dword at offset 0x38 is not above the second, the dword at offset 0x3c has only the
// bits of the third argument set, and the dword at offset 0x40 is not above the fourth argument,
// otherwise 0. File offset 0x1034e0, VA 0x10a034e0. The class and method names are invented; the
// offsets are the binary's. The meanings of the fields are guesses.

class UnkType_10a034e0
{
public:
    int UnkMethod_10a034e0(int a, int b, int mask, int d);

private:
    unsigned char unk_00[0x34];     // not read by this function
    int unk_34;
    int unk_38;
    unsigned int unk_3c;
    int unk_40;
};

// UnkType_10a034e0::UnkMethod_10a034e0
int UnkType_10a034e0::UnkMethod_10a034e0(int a, int b, int mask, int d)
{
    if (unk_34 >= a && unk_38 >= b && (unk_3c & mask) == unk_3c && unk_40 <= d)
        return 1;
    return 0;
}
