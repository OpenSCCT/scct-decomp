// campaign_leaf_1ffb90.cpp -- returns whether the flag byte of the entry at index (the argument
// modulo 40) is nonzero. The entries are 8 bytes each, starting at offset 0x10 of this. File offset
// 0x1ffb90, VA 0x10affb90. The class and method names are invented; the offsets are the binary's.
// The entry layout and the meaning of the flag are guesses.

class UnkType_10affb90Entry
{
public:
    unsigned char unk_00;
    unsigned char unk_01[0x07];
};

class UnkType_10affb90
{
public:
    int UnkMethod_10affb90(unsigned int index);

private:
    unsigned char unk_00[0x10];     // not read by this function
    UnkType_10affb90Entry unk_10[40];
};

// UnkType_10affb90::UnkMethod_10affb90
int UnkType_10affb90::UnkMethod_10affb90(unsigned int index)
{
    return unk_10[index % 40].unk_00 != 0;
}
