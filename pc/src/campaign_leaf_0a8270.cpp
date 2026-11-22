// campaign_leaf_0a8270.cpp -- one function at file offset 0xa8270, preferred VA 0x109a8270. It
// copies the sixteen words that its pointer argument points to into the block at offset 0x58 of
// this object. The class and method names are invented; the offset and the bytes are the binary's.

struct UnkType_109a8270_Block
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
    int unk_30;
    int unk_34;
    int unk_38;
    int unk_3c;
};

class UnkType_109a8270
{
public:
    void UnkCopyBlock(const UnkType_109a8270_Block *Src);

private:
    unsigned char unk_00[0x58];    // not read by this function
    UnkType_109a8270_Block unk_58;
};

// UnkType_109a8270::UnkCopyBlock
void UnkType_109a8270::UnkCopyBlock(const UnkType_109a8270_Block *Src)
{
    unk_58 = *Src;
}
