// campaign_band2_byte_24.cpp -- getters for the byte at offset 0x24 and the word at 0x20. The class
// and method names are invented; the offsets are the binary's.

class UnkType_10da2420
{
public:
    unsigned char GetUnk24();
    int GetUnk20();

private:
    unsigned char unk_00[0x20];    // not read by any function in this unit
    int unk_20;
    unsigned char unk_24;
};

// UnkType_10da2420::GetUnk24
unsigned char UnkType_10da2420::GetUnk24()
{
    return unk_24;
}

// UnkType_10da2420::GetUnk20
int UnkType_10da2420::GetUnk20()
{
    return unk_20;
}
