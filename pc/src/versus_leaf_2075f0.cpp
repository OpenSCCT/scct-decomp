// versus_leaf_2075f0.cpp -- returns the float at 0x168 when the int at 0x160 is nonzero, else the float at 0x170, at file offset 0x2075f0 (VA 0x10b075f0).
// The class, member and method names are invented; the offsets and the argument sizes
// are the binary's.

class UnkType_10b075f0
{
public:
    float GetUnk168Or170();

private:
    unsigned char unk_00[0x160];        // not read by this function
    int unk_160;                        // selects the float
    unsigned char unk_164[0x168 - 0x164];  // not read by this function
    float unk_168;                      // returned when unk_160 is nonzero
    unsigned char unk_16c[0x170 - 0x16c];  // not read by this function
    float unk_170;                      // returned when unk_160 is zero
};

// UnkType_10b075f0::GetUnk168Or170
float UnkType_10b075f0::GetUnk168Or170()
{
    if ( unk_160 == 0 )
        return unk_170;
    return unk_168;
}
