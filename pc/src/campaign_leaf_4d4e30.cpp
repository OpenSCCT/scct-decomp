// campaign_leaf_4d4e30.cpp -- one function at file offset 0x4d4e30, preferred VA 0x10dd4e30.
// It calls the method at 0x10dd4b10 and returns whether the pointer at offset 8 is non-null. The
// class, method and member names are invented; the offset and the bytes are the binary's.

class UnkType_10dd4e30
{
public:
    int unk_0;
    int unk_4;
    void* unk_8;

    void Unk_10dd4b10();
    bool Unk_10dd4e30();
};

// UnkType_10dd4e30::Unk_10dd4e30
bool UnkType_10dd4e30::Unk_10dd4e30()
{
    Unk_10dd4b10();
    return unk_8 != 0;
}
