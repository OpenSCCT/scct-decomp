// campaign_leaf_1acbd0.cpp -- returns the dword at offset 0x68 of this and stores 1 there when the
// argument is zero, otherwise 0. File offset 0x1acbd0, VA 0x10aacbd0. The class and method names
// are invented; the offsets are the binary's. The meaning of the stored flag is a guess.

class UnkType_10aacbd0
{
public:
    int UnkMethod_10aacbd0(int value);

private:
    unsigned char unk_00[0x68];     // not read by this function
    int unk_68;
};

// UnkType_10aacbd0::UnkMethod_10aacbd0
int UnkType_10aacbd0::UnkMethod_10aacbd0(int value)
{
    int previous = unk_68;
    unk_68 = value == 0;
    return previous;
}
