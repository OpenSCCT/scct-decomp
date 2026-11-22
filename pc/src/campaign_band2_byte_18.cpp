// campaign_band2_byte_18.cpp -- the low three bits of the byte at offset 0xa, and set and get the
// byte at 0x18. The class and method names are invented; the offsets and the mask are the binary's.

class UnkType_10de05b0
{
public:
    int GetUnk0aLowBits();
    void SetUnk18(unsigned char Value);
    unsigned char GetUnk18();

private:
    unsigned char unk_00[0xa];    // not read by any function in this unit
    unsigned char unk_0a;         // only its low three bits are read
    unsigned char unk_0b[0xd];    // not read by any function in this unit
    unsigned char unk_18;
};

// UnkType_10de05b0::GetUnk0aLowBits
int UnkType_10de05b0::GetUnk0aLowBits()
{
    return unk_0a & 7;
}

// UnkType_10de05b0::SetUnk18
void UnkType_10de05b0::SetUnk18(unsigned char Value)
{
    unk_18 = Value;
}

// UnkType_10de05b0::GetUnk18
unsigned char UnkType_10de05b0::GetUnk18()
{
    return unk_18;
}
