// campaign_band2_byte_14.cpp -- set and get the byte at offset 0x14. The word getter before them,
// at VA 0x10db77e0, is matched elsewhere. The class and method names are invented; the offset is
// the binary's.

class UnkType_10db77f0
{
public:
    void SetUnk14(unsigned char Value);
    unsigned char GetUnk14();

private:
    unsigned char unk_00[0x14];    // not read by any function in this unit
    unsigned char unk_14;
};

// UnkType_10db77f0::SetUnk14
void UnkType_10db77f0::SetUnk14(unsigned char Value)
{
    unk_14 = Value;
}

// UnkType_10db77f0::GetUnk14
unsigned char UnkType_10db77f0::GetUnk14()
{
    return unk_14;
}
