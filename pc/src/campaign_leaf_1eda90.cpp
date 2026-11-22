// campaign_leaf_1eda90.cpp -- returns 1 when this is compatible with the argument: the dwords at
// offsets 0x34 and 0x38 are not below the argument's, the bits of the dword at 0x3c are all set in
// the argument's dword there, and the dword at 0x40 is not above the larger of the argument's dword
// there and 0x4b0; otherwise 0. File offset 0x1eda90, VA 0x10aeda90. The class and method names are
// invented; the offsets are the binary's. The meanings of the fields are guesses.

class UnkType_10aeda90
{
public:
    int UnkMethod_10aeda90(UnkType_10aeda90 *other);

private:
    unsigned char unk_00[0x34];     // not read by this function
    int unk_34;
    int unk_38;
    int unk_3c;
    int unk_40;
};

// UnkType_10aeda90::UnkMethod_10aeda90
int UnkType_10aeda90::UnkMethod_10aeda90(UnkType_10aeda90 *other)
{
    if (unk_34 >= other->unk_34 && unk_38 >= other->unk_38 && (unk_3c | other->unk_3c) == other->unk_3c)
    {
        int limit = other->unk_40;
        if (limit <= 0x4b0)
            limit = 0x4b0;
        if (unk_40 <= limit)
            return 1;
    }
    return 0;
}
