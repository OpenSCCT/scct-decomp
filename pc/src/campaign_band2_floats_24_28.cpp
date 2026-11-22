// campaign_band2_floats_24_28.cpp -- getters for the floats at offsets 0x24 and 0x28. The setter of
// 0x28 before them, at VA 0x10e5b340, is matched elsewhere. The class and method names are
// invented; the offsets are the binary's.

class UnkType_10e5b350
{
public:
    float GetUnk24();
    float GetUnk28();

private:
    unsigned char unk_00[0x24];    // not read by any function in this unit
    float unk_24;
    float unk_28;
};

// UnkType_10e5b350::GetUnk24
float UnkType_10e5b350::GetUnk24()
{
    return unk_24;
}

// UnkType_10e5b350::GetUnk28
float UnkType_10e5b350::GetUnk28()
{
    return unk_28;
}
