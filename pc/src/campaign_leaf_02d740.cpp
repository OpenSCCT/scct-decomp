// campaign_leaf_02d740.cpp -- one function at file offset 0x2d740, preferred VA 0x1092d740. It
// copies four three-word blocks, given by four pointers, into the four slots of this object, and
// returns this object. The class, struct, method and parameter names are invented; the offset and
// the bytes are the binary's.

struct UnkType_1092d740_Triple
{
    int unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_1092d740
{
public:
    UnkType_1092d740 *UnkSetVectors(const UnkType_1092d740_Triple *First,
                                    const UnkType_1092d740_Triple *Second,
                                    const UnkType_1092d740_Triple *Third,
                                    const UnkType_1092d740_Triple *Fourth);

private:
    UnkType_1092d740_Triple unk_00[4];  // four 12-byte slots, at offsets 0x00, 0x0c, 0x18 and 0x24
};

// UnkType_1092d740::UnkSetVectors
UnkType_1092d740 *UnkType_1092d740::UnkSetVectors(const UnkType_1092d740_Triple *First,
                                                  const UnkType_1092d740_Triple *Second,
                                                  const UnkType_1092d740_Triple *Third,
                                                  const UnkType_1092d740_Triple *Fourth)
{
    unk_00[0] = *First;
    unk_00[1] = *Second;
    unk_00[2] = *Third;
    unk_00[3] = *Fourth;
    return this;
}
