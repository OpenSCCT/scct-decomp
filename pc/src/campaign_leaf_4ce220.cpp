// campaign_leaf_4ce220.cpp -- one function at file offset 0x4ce220, preferred VA 0x10dce220.
// It calls the method at 0x10dce120 with the ints at offsets 8 and 0xc of Other and -1, and returns
// this object. The class, method and parameter names are invented; the offset and the bytes are
// the binary's.

class UnkType_10dce220
{
public:
    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;

    void Unk_10dce120(int First, int Second, int Count);
    UnkType_10dce220& Unk_10dce220(const UnkType_10dce220& Other);
};

// UnkType_10dce220::Unk_10dce220
UnkType_10dce220& UnkType_10dce220::Unk_10dce220(const UnkType_10dce220& Other)
{
    Unk_10dce120(Other.unk_8, Other.unk_c, -1);
    return *this;
}
