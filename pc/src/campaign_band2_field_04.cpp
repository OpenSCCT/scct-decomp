// campaign_band2_field_04.cpp -- returns the word at offset 4. The class and method names are
// invented; the offset is the binary's.

class UnkType_10da7440
{
public:
    int GetUnk04();

private:
    unsigned char unk_00[0x4];    // not read by any function in this unit
    int unk_04;
};

// UnkType_10da7440::GetUnk04
int UnkType_10da7440::GetUnk04()
{
    return unk_04;
}
