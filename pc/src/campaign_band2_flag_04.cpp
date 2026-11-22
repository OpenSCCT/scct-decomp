// campaign_band2_flag_04.cpp -- sets the byte flag at offset 4. The class and method names are
// invented; the offset is the binary's.

class UnkType_10da4810
{
public:
    void SetUnk04();

private:
    unsigned char unk_00[0x4];    // not read by any function in this unit
    unsigned char unk_04;
};

// UnkType_10da4810::SetUnk04
void UnkType_10da4810::SetUnk04()
{
    unk_04 = 1;
}
