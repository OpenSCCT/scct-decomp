// campaign_band2_signed_short_0a.cpp -- two identical getters that widen the signed 16-bit field at
// offset 0xa. Retail keeps both copies, at VA 0x10e02db0 and 0x10e02dc0. The class and method names
// are invented; the offset is the binary's.

class UnkType_10e02db0
{
public:
    int GetUnk0a();

private:
    unsigned char unk_00[0xa];    // not read by any function in this unit
    short unk_0a;
};

// UnkType_10e02db0::GetUnk0a
int UnkType_10e02db0::GetUnk0a()
{
    return unk_0a;
}
