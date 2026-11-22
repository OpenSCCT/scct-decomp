// versus_leaf_210140.cpp -- the low bit of the int member at 0x1a4 of the object, at file offset 0x210140 (VA 0x10b10140).
// The class, member, element and method names are invented; the offsets, the element
// strides and the argument sizes are the binary's.

class UnkType_10b10140
{
public:
    int GetUnk1A4Bit0();

private:
    unsigned char unk_00[0x1a4];        // not read by this function
    int unk_1a4;                        // read by GetUnk1A4Bit0
};

// UnkType_10b10140::GetUnk1A4Bit0
int UnkType_10b10140::GetUnk1A4Bit0()
{
    return unk_1a4 & 1;
}
