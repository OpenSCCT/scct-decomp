// campaign_band2_bytes_04_05.cpp -- getters for the bytes at offsets 5 and 4. The class and method
// names are invented; the offsets are the binary's.

class UnkType_10da78e0
{
public:
    unsigned char GetUnk05();
    unsigned char GetUnk04();

private:
    unsigned char unk_00[0x4];    // not read by any function in this unit
    unsigned char unk_04;
    unsigned char unk_05;
};

// UnkType_10da78e0::GetUnk05
unsigned char UnkType_10da78e0::GetUnk05()
{
    return unk_05;
}

// UnkType_10da78e0::GetUnk04
unsigned char UnkType_10da78e0::GetUnk04()
{
    return unk_04;
}
