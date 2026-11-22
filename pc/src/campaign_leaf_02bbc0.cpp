// campaign_leaf_02bbc0.cpp -- one function at file offset 0x2bbc0, preferred VA 0x1092bbc0. It
// clears the bytes at offsets 0x22d and 0x22f of this object. The class and method names are
// invented; the offset and the bytes are the binary's.

class UnkType_1092bbc0
{
public:
    void UnkClearFlags();

private:
    unsigned char unk_00[0x22d];    // not touched by this function
    unsigned char unk_22d;          // cleared
    unsigned char unk_22e;          // not touched by this function
    unsigned char unk_22f;          // cleared
};

// UnkType_1092bbc0::UnkClearFlags
void UnkType_1092bbc0::UnkClearFlags()
{
    unk_22d = 0;
    unk_22f = 0;
}
