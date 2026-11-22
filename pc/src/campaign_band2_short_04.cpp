// campaign_band2_short_04.cpp -- returns the 16-bit field at offset 4. The class and method names
// are invented; the offset is the binary's.

class UnkType_10da4730
{
public:
    unsigned short GetUnk04();

private:
    unsigned char unk_00[0x4];    // not read by any function in this unit
    unsigned short unk_04;
};

// UnkType_10da4730::GetUnk04
unsigned short UnkType_10da4730::GetUnk04()
{
    return unk_04;
}
