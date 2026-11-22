// campaign_leaf_123bd0.cpp -- copies the 20-byte block at offset 0x14c of the argument to offset
// 0x160 of the argument, when the argument is not null, the byte at offset 0x114 or 0xfc of this has
// bit 0 set, and the byte at offset 0x364 of this has bit 3 set. File offset 0x123bd0, VA
// 0x10a23bd0. The class and method names are invented; the offsets are the binary's. The meanings of
// the fields are guesses.

class UnkType_10a23bd0Block
{
public:
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
    int unk_10;
};

class UnkType_10a23bd0
{
public:
    void UnkMethod_10a23bd0(UnkType_10a23bd0 *other);

private:
    unsigned char unk_00[0xfc];     // not read by this function
    unsigned char unk_fc;
    unsigned char unk_fd[0x17];     // not read by this function
    unsigned char unk_114;
    unsigned char unk_115[0x37];    // not read by this function
    UnkType_10a23bd0Block unk_14c;
    UnkType_10a23bd0Block unk_160;
    unsigned char unk_174[0x1f0];   // not read by this function
    unsigned char unk_364;
};

// UnkType_10a23bd0::UnkMethod_10a23bd0
void UnkType_10a23bd0::UnkMethod_10a23bd0(UnkType_10a23bd0 *other)
{
    if (other == 0)
        return;
    if ((unk_114 & 1) == 0 && (unk_fc & 1) == 0)
        return;
    if ((unk_364 & 8) == 0)
        return;
    other->unk_160 = other->unk_14c;
}
