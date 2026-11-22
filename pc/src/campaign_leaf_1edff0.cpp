// campaign_leaf_1edff0.cpp -- sets the bit 0x40 of the dword at offset 0x08 of this when the
// argument is nonzero, and clears it otherwise. File offset 0x1edff0, VA 0x10aedff0. The class and
// method names are invented; the offsets are the binary's. The meaning of the bit is a guess.

class UnkType_10aedff0
{
public:
    void UnkMethod_10aedff0(int value);

private:
    unsigned char unk_00[0x08];     // not read by this function
    int unk_08;
};

// UnkType_10aedff0::UnkMethod_10aedff0
void UnkType_10aedff0::UnkMethod_10aedff0(int value)
{
    if (value != 0)
        unk_08 |= 0x40;
    else
        unk_08 &= ~0x40;
}
