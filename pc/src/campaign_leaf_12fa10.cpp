// campaign_leaf_12fa10.cpp -- clears bit 0x01 of the dwords at offsets 0x2c and 0x44 of this. The
// argument is not read. File offset 0x12fa10, VA 0x10a2fa10. The class and method names are
// invented; the offsets are the binary's.

class UnkType_10a2fa10
{
public:
    void ClearBit0Unk2CAndUnk44(int);

private:
    unsigned char unk_00[0x2c];     // not read by this function
    unsigned int unk_2c;
    unsigned char unk_30[0x14];     // not read by this function
    unsigned int unk_44;
};

// UnkType_10a2fa10::ClearBit0Unk2CAndUnk44
void UnkType_10a2fa10::ClearBit0Unk2CAndUnk44(int)
{
    unk_2c &= 0xfffffffe;
    unk_44 &= 0xfffffffe;
}
