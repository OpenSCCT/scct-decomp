// campaign_leaf_1d55e0.cpp -- returns the first dword of the last record in the table at offset
// 0x24 of this, counting from the count at offset 0x28, or -1 when the flag at offset 0x31 is clear,
// the count is zero or the record is null. File offset 0x1d55e0, VA 0x10ad55e0. The class and
// method names are invented; the offsets are the binary's. The types and the meanings are guesses.

class UnkType_10ad55e0Record
{
public:
    int unk_00;
};

class UnkType_10ad55e0
{
public:
    int UnkMethod_10ad55e0();

private:
    unsigned char unk_00[0x24];     // not read by this function
    UnkType_10ad55e0Record **unk_24;
    int unk_28;
    unsigned char unk_2c[0x05];     // not read by this function
    unsigned char unk_31;
};

// UnkType_10ad55e0::UnkMethod_10ad55e0
int UnkType_10ad55e0::UnkMethod_10ad55e0()
{
    if (unk_31 == 0 || unk_28 == 0)
        return -1;
    UnkType_10ad55e0Record *record = unk_24[unk_28 - 1];
    if (record == 0)
        return -1;
    return record->unk_00;
}
