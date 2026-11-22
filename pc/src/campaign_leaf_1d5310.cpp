// campaign_leaf_1d5310.cpp -- returns the number of 60-byte records between the two record pointers
// at offsets 0x6c and 0x70 of this, or zero when the begin pointer is null. File offset 0x1d5310,
// VA 0x10ad5310. The class and method names are invented; the offsets are the binary's. The record
// size comes from the division by 60 in the binary; the record type is a guess.

class UnkType_10ad5310Record
{
public:
    unsigned char unk_00[0x3c];
};

class UnkType_10ad5310
{
public:
    int UnkMethod_10ad5310();

private:
    unsigned char unk_00[0x6c];     // not read by this function
    UnkType_10ad5310Record *unk_6c;
    UnkType_10ad5310Record *unk_70;
};

// UnkType_10ad5310::UnkMethod_10ad5310
int UnkType_10ad5310::UnkMethod_10ad5310()
{
    if (unk_6c == 0)
        return 0;
    return unk_70 - unk_6c;
}
