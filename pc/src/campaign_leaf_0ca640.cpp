// campaign_leaf_0ca640.cpp -- one function at file offset 0xca640, preferred VA 0x109ca640. It
// copies the three-word blocks that its second, third and fourth arguments point to into the
// blocks at offsets 0x18, 0x24 and 0x30 of this object. Its first argument is not used. The class
// and method names are invented; the offset and the bytes are the binary's.

struct UnkType_109ca640_Triple
{
    int unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_109ca640
{
public:
    void UnkSetThree(int Unused, const UnkType_109ca640_Triple *First,
                     const UnkType_109ca640_Triple *Second, const UnkType_109ca640_Triple *Third);

private:
    unsigned char unk_00[0x18];     // not read by this function
    UnkType_109ca640_Triple unk_18;
    UnkType_109ca640_Triple unk_24;
    UnkType_109ca640_Triple unk_30;
};

// UnkType_109ca640::UnkSetThree
void UnkType_109ca640::UnkSetThree(int Unused, const UnkType_109ca640_Triple *First,
                                    const UnkType_109ca640_Triple *Second,
                                    const UnkType_109ca640_Triple *Third)
{
    unk_18 = *First;
    unk_24 = *Second;
    unk_30 = *Third;
}
