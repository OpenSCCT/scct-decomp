// campaign_leaf_1c6090.cpp -- returns the dword at offset 0x68 of this and stores 1 there when the
// argument is zero, otherwise 0. File offset 0x1c6090, VA 0x10ac6090. The class and method names
// are invented; the offsets are the binary's. The meaning of the stored flag is a guess.

class UnkType_10ac6090
{
public:
    int UnkMethod_10ac6090(int value);

private:
    unsigned char unk_00[0x68];     // not read by this function
    int unk_68;
};

// UnkType_10ac6090::UnkMethod_10ac6090
int UnkType_10ac6090::UnkMethod_10ac6090(int value)
{
    int previous = unk_68;
    unk_68 = value == 0;
    return previous;
}
