// campaign_leaf_08fcf0.cpp -- one function at file offset 0x8fcf0, preferred VA 0x1098fcf0. It
// sets the bit numbered by the byte at offset 0xb4 in the word array at offset 0x3ab0 of the
// object at offset 0x7c. The element count is not established. The class and method names are
// invented; the offset and the bytes are the binary's.

struct UnkType_1098fcf0_Bits
{
    unsigned char unk_00[0x3ab0];   // not read by this function
    unsigned int unk_3ab0[1];       // bit words; the element count is not established
};

class UnkType_1098fcf0
{
public:
    void UnkSetBit();

private:
    unsigned char unk_00[0x7c];     // not read by this function
    UnkType_1098fcf0_Bits *unk_7c;
    unsigned char unk_80[0x34];     // not read by this function
    unsigned char unk_b4;
};

// UnkType_1098fcf0::UnkSetBit
void UnkType_1098fcf0::UnkSetBit()
{
    int Index = unk_b4;
    unsigned int *Words = unk_7c->unk_3ab0;
    Words[Index >> 5] |= 1 << ( Index & 0x1f );
}
