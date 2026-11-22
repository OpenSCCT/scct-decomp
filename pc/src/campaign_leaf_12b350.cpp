// campaign_leaf_12b350.cpp -- returns the dword at offset 0x2c of this when it is not -1 and bit
// 0x01 of the byte at offset 0x28 is set, otherwise -1. File offset 0x12b350, VA 0x10a2b350. The
// class and method names are invented; the offsets are the binary's.

class UnkType_10a2b350
{
public:
    int GetUnk2CIfFlag28();

private:
    unsigned char unk_00[0x28];     // not read by this function
    unsigned char unk_28;           // bit 0x01 is tested
    unsigned char unk_29[3];        // not read by this function
    int unk_2c;
};

// UnkType_10a2b350::GetUnk2CIfFlag28
int UnkType_10a2b350::GetUnk2CIfFlag28()
{
    if ( unk_2c != -1 && ( unk_28 & 1 ) )
    {
        return unk_2c;
    }
    return -1;
}
