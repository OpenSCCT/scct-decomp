// versus_leaf_204b90.cpp -- the first int of element n - 1 of the array at 0x108, where n is the int at 0x1a4, or 0 when n is 0, at file offset 0x204b90 (VA 0x10b04b90).
// The class, member, element and method names are invented; the offsets, the element
// strides and the argument sizes are the binary's.

struct UnkElement_10b04b90
{
    int unk_00;                         // read by GetUnk108_1A4
    unsigned char unk_04[0x68 - 0x04];  // the element stride is 0x68
};

class UnkType_10b04b90
{
public:
    int GetUnk108_1A4();

private:
    unsigned char unk_00[0x108];        // not read by this function except through the array
    UnkElement_10b04b90 *unk_108;
    unsigned char unk_10c[0x1a4 - 0x10c];  // not read by this function
    int unk_1a4;                        // the count, 1-based index of the element read
};

// UnkType_10b04b90::GetUnk108_1A4
int UnkType_10b04b90::GetUnk108_1A4()
{
    if ( unk_1a4 != 0 )
        return unk_108[unk_1a4 - 1].unk_00;
    return 0;
}
