// campaign_band2_float_28.cpp -- returns the float at offset 0x28. The class and method names are
// invented; the offset is the binary's.

class UnkType_10dc8670
{
public:
    float GetUnk28();

private:
    unsigned char unk_00[0x28];    // not read by any function in this unit
    float unk_28;
};

// UnkType_10dc8670::GetUnk28
float UnkType_10dc8670::GetUnk28()
{
    return unk_28;
}
