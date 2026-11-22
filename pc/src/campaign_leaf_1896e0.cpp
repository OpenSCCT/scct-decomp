// campaign_leaf_1896e0.cpp -- sets bit 0x2000 of the dword at offset 0x300 of this. File offset
// 0x1896e0, VA 0x10a896e0. The class and method names are invented; the offsets are the binary's.

class UnkType_10a896e0
{
public:
    void SetUnk300Bit13();

private:
    unsigned char unk_00[0x300];    // not read by this function
    unsigned int unk_300;
};

// UnkType_10a896e0::SetUnk300Bit13
void UnkType_10a896e0::SetUnk300Bit13()
{
    unk_300 |= 0x2000;
}
