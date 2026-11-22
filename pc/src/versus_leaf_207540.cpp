// versus_leaf_207540.cpp -- returns the float at 0x164 when the int at 0x160 is nonzero, else the float at 0x178, at file offset 0x207540 (VA 0x10b07540).
// The class, member and method names are invented; the offsets and the argument sizes
// are the binary's.

class UnkType_10b07540
{
public:
    float GetUnk164Or178();

private:
    unsigned char unk_00[0x160];        // not read by this function
    int unk_160;                        // selects the float
    float unk_164;                      // returned when unk_160 is nonzero
    unsigned char unk_168[0x178 - 0x168];  // not read by this function
    float unk_178;                      // returned when unk_160 is zero
};

// UnkType_10b07540::GetUnk164Or178
float UnkType_10b07540::GetUnk164Or178()
{
    if ( unk_160 == 0 )
        return unk_178;
    return unk_164;
}
