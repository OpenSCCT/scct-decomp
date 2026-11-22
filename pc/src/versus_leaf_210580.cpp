// versus_leaf_210580.cpp -- the int at 0x4 of the object that the member at 0x190 of the object points to, at file offset 0x210580 (VA 0x10b10580).
// The class, member, element and method names are invented; the offsets, the element
// strides and the argument sizes are the binary's.

struct UnkPointee_10b10580
{
    unsigned char unk_00[0x4];
    int unk_04;                         // read by GetUnk190_04
};

class UnkType_10b10580
{
public:
    int GetUnk190_04();

private:
    unsigned char unk_00[0x190];        // not read by this function
    UnkPointee_10b10580 *unk_190;
};

// UnkType_10b10580::GetUnk190_04
int UnkType_10b10580::GetUnk190_04()
{
    return unk_190->unk_04;
}
