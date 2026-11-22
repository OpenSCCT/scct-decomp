// campaign_leaf_0ca3e0.cpp -- one function at file offset 0xca3e0, preferred VA 0x109ca3e0. It
// copies the twelve words at offset 0x1a0 of this object to the block at offset 0x128. The class
// and method names are invented; the offset and the bytes are the binary's.

struct UnkType_109ca3e0_Block
{
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
    int unk_10;
    int unk_14;
    int unk_18;
    int unk_1c;
    int unk_20;
    int unk_24;
    int unk_28;
    int unk_2c;
};

class UnkType_109ca3e0
{
public:
    void UnkCopyInner();

private:
    unsigned char unk_00[0x128];    // not read by this function
    UnkType_109ca3e0_Block unk_128;
    unsigned char unk_158[0x48];    // not read by this function
    UnkType_109ca3e0_Block unk_1a0;
};

// UnkType_109ca3e0::UnkCopyInner
void UnkType_109ca3e0::UnkCopyInner()
{
    unk_128 = unk_1a0;
}
