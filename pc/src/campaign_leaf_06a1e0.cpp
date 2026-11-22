// campaign_leaf_06a1e0.cpp -- one function at file offset 0x6a1e0, preferred VA 0x1096a1e0. It
// stores 1 through its second argument when bit 2 of the flag byte at offset 0x6c is set, and
// through its third argument when bit 1 is set. Its first and last three arguments are not used. It
// returns this object. The class, method and parameter names are invented; the offset and the bytes
// are the binary's.

class UnkType_1096a1e0
{
public:
    const UnkType_1096a1e0 *UnkSetOutputs(int First, int *Second, int *Third, int Fourth, int Fifth,
                                          int Sixth) const;

private:
    unsigned char unk_00[0x6c];     // not read by this function
    unsigned char unk_6c;           // flag byte, bits 1 and 2 tested
};

// UnkType_1096a1e0::UnkSetOutputs
const UnkType_1096a1e0 *UnkType_1096a1e0::UnkSetOutputs(int First, int *Second, int *Third,
                                                        int Fourth, int Fifth, int Sixth) const
{
    if ( ( unk_6c & 2 ) != 0 )
    {
        *Second = 1;
    }
    if ( ( unk_6c & 1 ) != 0 )
    {
        *Third = 1;
    }
    return this;
}
