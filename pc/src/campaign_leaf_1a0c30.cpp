// campaign_leaf_1a0c30.cpp -- copies the five dwords at the argument to the member at offset 0x90
// of this. File offset 0x1a0c30, VA 0x10aa0c30. The class and method names are invented; the
// offsets are the binary's, and the block type is a guess.

class UnkBlock_10aa0c30
{
public:
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
    int unk_10;
};

class UnkType_10aa0c30
{
public:
    void UnkMethod_10aa0c30(UnkBlock_10aa0c30 *Src);

private:
    unsigned char unk_00[0x90];     // not read by this function
    UnkBlock_10aa0c30 unk_90;
};

// UnkType_10aa0c30::UnkMethod_10aa0c30
void UnkType_10aa0c30::UnkMethod_10aa0c30(UnkBlock_10aa0c30 *Src)
{
    unk_90 = *Src;
}
