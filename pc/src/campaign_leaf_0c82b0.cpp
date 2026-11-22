// campaign_leaf_0c82b0.cpp -- one function at file offset 0xc82b0, preferred VA 0x109c82b0. It
// sets the word at offset 0x174 to zero and the float at offset 0x178 to 1.0. The class and method
// names are invented; the offset and the bytes are the binary's.

class UnkType_109c82b0
{
public:
    void UnkResetPair();

private:
    unsigned char unk_00[0x174];    // not read by this function
    int unk_174;
    float unk_178;
};

// UnkType_109c82b0::UnkResetPair
void UnkType_109c82b0::UnkResetPair()
{
    unk_174 = 0;
    unk_178 = 1.0f;
}
