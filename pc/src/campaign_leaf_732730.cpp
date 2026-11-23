// campaign_leaf_732730.cpp -- one function at file offset 0x732730, preferred VA 0x11032730. It
// calls the methods at VA 0x11032db0 and VA 0x11032840 on this and returns true. The class and
// method names are invented; the offset and the addresses are the binary's.

class UnkType_11032730
{
public:
    bool Unk_11032730();
    void Unk_11032db0();
    void Unk_11032840();
};

// UnkType_11032730::Unk_11032730
bool UnkType_11032730::Unk_11032730()
{
    Unk_11032db0();
    Unk_11032840();
    return true;
}
