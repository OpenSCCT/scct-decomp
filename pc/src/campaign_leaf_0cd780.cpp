// campaign_leaf_0cd780.cpp -- one function at file offset 0xcd780, preferred VA 0x109cd780. It
// stores its argument in the word at offset 0x54. The class and method names are invented; the
// offset and the bytes are the binary's.

class UnkType_109cd780
{
public:
    void UnkSet54(int Value);

private:
    unsigned char unk_00[0x54];     // not read by this function
    int unk_54;
};

// UnkType_109cd780::UnkSet54
void UnkType_109cd780::UnkSet54(int Value)
{
    unk_54 = Value;
}
