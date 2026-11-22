// campaign_leaf_1a0c60.cpp -- copies the five dwords of the member at offset 0x90 of this to the
// argument. File offset 0x1a0c60, VA 0x10aa0c60. The class and method names are invented; the
// offsets are the binary's, and the block type is a guess.

class UnkBlock_10aa0c60
{
public:
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
    int unk_10;
};

class UnkType_10aa0c60
{
public:
    void UnkMethod_10aa0c60(UnkBlock_10aa0c60 *Dst);

private:
    unsigned char unk_00[0x90];     // not read by this function
    UnkBlock_10aa0c60 unk_90;
};

// UnkType_10aa0c60::UnkMethod_10aa0c60
void UnkType_10aa0c60::UnkMethod_10aa0c60(UnkBlock_10aa0c60 *Dst)
{
    *Dst = unk_90;
}
