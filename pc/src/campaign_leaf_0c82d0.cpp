// campaign_leaf_0c82d0.cpp -- one function at file offset 0xc82d0, preferred VA 0x109c82d0. It
// sets the float at offset 0x174 to 1.0 and the word at offset 0x178 to zero. The class and method
// names are invented; the offset and the bytes are the binary's.

class UnkType_109c82d0
{
public:
    void UnkResetPair();

private:
    unsigned char unk_00[0x174];    // not read by this function
    float unk_174;
    int unk_178;
};

// UnkType_109c82d0::UnkResetPair
void UnkType_109c82d0::UnkResetPair()
{
    unk_174 = 1.0f;
    unk_178 = 0;
}
