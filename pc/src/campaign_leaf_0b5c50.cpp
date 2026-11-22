// campaign_leaf_0b5c50.cpp -- one function at file offset 0xb5c50, preferred VA 0x109b5c50. It
// sets the word at offset 0x1cc to 1 and ignores its argument. The class and method names are
// invented; the offset and the bytes are the binary's.

class UnkType_109b5c50
{
public:
    void UnkSetFlag(int Value);

private:
    unsigned char unk_00[0x1cc];    // not read by this function
    int unk_1cc;
};

// UnkType_109b5c50::UnkSetFlag
void UnkType_109b5c50::UnkSetFlag(int Value)
{
    unk_1cc = 1;
}
