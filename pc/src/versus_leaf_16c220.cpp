// versus_leaf_16c220.cpp -- the int at 0xc of the 0x68-byte row at Index of the table at 0x808 of the object at 0x30, at file offset 0x16c220 (VA 0x10a6c220).
// The class, member, element and method names are invented; the offsets, the element
// strides and the argument sizes are the binary's.

struct UnkRow_10a6c220
{
    unsigned char unk_00[0xc];
    int unk_0c;                         // read by GetUnk30_808_0C
    unsigned char unk_10[0x68 - 0x10];  // the row stride is 0x68
};

struct UnkTable_10a6c220
{
    UnkRow_10a6c220 *unk_00;                 // the rows
};

struct UnkParent_10a6c220
{
    unsigned char unk_00[0x808];
    UnkTable_10a6c220 *unk_808;
};

class UnkType_10a6c220
{
public:
    int GetUnk30_808_0C(int Index);

private:
    unsigned char unk_00[0x30];         // not read by this function
    UnkParent_10a6c220 *unk_30;
};

// UnkType_10a6c220::GetUnk30_808_0C
int UnkType_10a6c220::GetUnk30_808_0C(int Index)
{
    return unk_30->unk_808->unk_00[Index].unk_0c;
}
