// campaign_leaf_0c9a00.cpp -- one function at file offset 0xc9a00, preferred VA 0x109c9a00. It
// stores its two arguments in the words at offsets 0x344 and 0x348. The class and method names are
// invented; the offset and the bytes are the binary's.

class UnkType_109c9a00
{
public:
    void UnkSetPair(int First, int Second);

private:
    unsigned char unk_00[0x344];    // not read by this function
    int unk_344;
    int unk_348;
};

// UnkType_109c9a00::UnkSetPair
void UnkType_109c9a00::UnkSetPair(int First, int Second)
{
    unk_344 = First;
    unk_348 = Second;
}
