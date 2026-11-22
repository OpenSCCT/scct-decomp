// campaign_band2_field_38.cpp -- returns the word at offset 0x38. The class and method names are
// invented; the offset is the binary's.

class UnkType_10d698d0
{
public:
    int GetUnk38();

private:
    unsigned char unk_00[0x38];    // not read by any function in this unit
    int unk_38;
};

// UnkType_10d698d0::GetUnk38
int UnkType_10d698d0::GetUnk38()
{
    return unk_38;
}
