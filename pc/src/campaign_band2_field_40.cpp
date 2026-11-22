// campaign_band2_field_40.cpp -- returns the word at offset 0x40. The class and method names are
// invented; the offset is the binary's.

class UnkType_10cccf70
{
public:
    int GetUnk40();

private:
    unsigned char unk_00[0x40];    // not read by any function in this unit
    int unk_40;
};

// UnkType_10cccf70::GetUnk40
int UnkType_10cccf70::GetUnk40()
{
    return unk_40;
}
