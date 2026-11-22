// campaign_leaf_1cde50.cpp -- returns the byte at offset 0x84 of this. File offset 0x1cde50,
// VA 0x10acde50. The class and method names are invented; the offsets are the binary's.

class UnkType_10acde50
{
public:
    unsigned char UnkMethod_10acde50();

private:
    unsigned char unk_00[0x84];     // not read by this function
    unsigned char unk_84;
};

// UnkType_10acde50::UnkMethod_10acde50
unsigned char UnkType_10acde50::UnkMethod_10acde50()
{
    return unk_84;
}
