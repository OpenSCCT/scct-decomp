// campaign_band2_field_ac.cpp -- set and get the word at offset 0xac, and a method that returns
// 0x10. The class and method names are invented; the offset and the constant are the binary's.

class UnkType_10de0670
{
public:
    void SetUnkAc(int Value);
    int GetUnkAc();
    unsigned short GetConstant10();

private:
    unsigned char unk_00[0xac];    // not read by any function in this unit
    int unk_ac;
};

// UnkType_10de0670::SetUnkAc
void UnkType_10de0670::SetUnkAc(int Value)
{
    unk_ac = Value;
}

// UnkType_10de0670::GetUnkAc
int UnkType_10de0670::GetUnkAc()
{
    return unk_ac;
}

// UnkType_10de0670::GetConstant10
//
// guess: a member of this class, from its place beside the others; it returns the 16-bit constant
// 0x10 and reads nothing.
unsigned short UnkType_10de0670::GetConstant10()
{
    return 0x10;
}
