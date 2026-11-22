// campaign_leaf_732730.cpp -- thiscall method at VA 0x11032730: calls the methods at VA 0x11032db0
// and VA 0x11032840 on the same object, then returns true. The class and method names are invented.

class UnkType_11032730
{
public:
    void Unk_11032db0();
    void Unk_11032840();
    bool Unk_11032730();
};

// UnkType_11032730::Unk_11032730
bool UnkType_11032730::Unk_11032730()
{
    Unk_11032db0();
    Unk_11032840();
    return true;
}
