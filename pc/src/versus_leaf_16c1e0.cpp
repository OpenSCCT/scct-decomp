// versus_leaf_16c1e0.cpp -- the int at 0x4 of the object at 0x808 of the object that the member at 0x30 points to, at file offset 0x16c1e0 (VA 0x10a6c1e0).
// The class, member, element and method names are invented; the offsets, the element
// strides and the argument sizes are the binary's.

struct UnkChild_10a6c1e0
{
    unsigned char unk_00[0x4];
    int unk_04;                         // read by GetUnk30_808_04
};

struct UnkParent_10a6c1e0
{
    unsigned char unk_00[0x808];
    UnkChild_10a6c1e0 *unk_808;
};

class UnkType_10a6c1e0
{
public:
    int GetUnk30_808_04();

private:
    unsigned char unk_00[0x30];         // not read by this function
    UnkParent_10a6c1e0 *unk_30;
};

// UnkType_10a6c1e0::GetUnk30_808_04
int UnkType_10a6c1e0::GetUnk30_808_04()
{
    return unk_30->unk_808->unk_04;
}
