// campaign_leaf_1d4be0.cpp -- returns the number of 60-byte records between the two record
// pointers of this, or zero when the begin pointer is null. File offset 0x1d4be0, VA 0x10ad4be0.
// The class and method names are invented; the offsets are the binary's. The record size comes from
// the division by 60 in the binary; the record type is a guess.

class UnkType_10ad4be0Record
{
public:
    unsigned char unk_00[0x3c];
};

class UnkType_10ad4be0
{
public:
    int UnkMethod_10ad4be0();

private:
    unsigned char unk_00[0x04];     // not read by this function
    UnkType_10ad4be0Record *unk_04;
    UnkType_10ad4be0Record *unk_08;
};

// UnkType_10ad4be0::UnkMethod_10ad4be0
int UnkType_10ad4be0::UnkMethod_10ad4be0()
{
    if (unk_04 == 0)
        return 0;
    return unk_08 - unk_04;
}
