// campaign_leaf_0b6b40.cpp -- one function at file offset 0xb6b40, preferred VA 0x109b6b40. It
// sets the words at offsets 0, 4, 8 and 0xc to zero, the half-words at 0x10, 0x12, 0x14 to zero,
// the half-words at 0x16 and 0x18 to 0xffff, and returns this object. The class and method names
// are invented; the offset and the bytes are the binary's.

class UnkType_109b6b40
{
public:
    UnkType_109b6b40 *UnkReset();

private:
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
    unsigned short unk_10;
    unsigned short unk_12;
    unsigned short unk_14;
    unsigned short unk_16;
    unsigned short unk_18;
};

// UnkType_109b6b40::UnkReset
UnkType_109b6b40 *UnkType_109b6b40::UnkReset()
{
    unk_00 = 0;
    unk_04 = 0;
    unk_08 = 0;
    unk_0c = 0;
    unk_12 = 0;
    unk_10 = 0;
    unk_14 = 0;
    unk_18 = 0xffff;
    unk_16 = 0xffff;
    return this;
}
