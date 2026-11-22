// campaign_leaf_0cd770.cpp -- one function at file offset 0xcd770, preferred VA 0x109cd770. It
// stores its argument in the word at offset 0x58. The class and method names are invented; the
// offset and the bytes are the binary's.

class UnkType_109cd770
{
public:
    void UnkSet58(int Value);

private:
    unsigned char unk_00[0x58];     // not read by this function
    int unk_58;
};

// UnkType_109cd770::UnkSet58
void UnkType_109cd770::UnkSet58(int Value)
{
    unk_58 = Value;
}
