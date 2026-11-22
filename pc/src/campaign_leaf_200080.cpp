// campaign_leaf_200080.cpp -- one leaf function at file offset 0x200080 (VA 0x10b00080).
// It takes an index and returns an int whose bit 0 is set when the flag of slot index % 40 of the
// table at this+0x10 is set, and whose bit 1 is set when the flag of the same slot of the table at
// this+0x164 is set. Both tables hold 8-byte slots. The class, member and field names are invented;
// the offsets and the table size are the binary's.

struct UnkSlot_10b00080
{
    unsigned char unk_00;           // the flag
    unsigned char unk_01[3];        // not read by this function
    unsigned int unk_04;            // not read by this function
};

class UnkType_10b00080
{
public:
    int UnkFn_10b00080(unsigned int Index);

private:
    unsigned char unk_00[0x10];     // not read by this function
    UnkSlot_10b00080 unk_10[40];
    unsigned char unk_150[0x14];    // not read by this function
    UnkSlot_10b00080 unk_164[40];
};

// UnkType_10b00080::UnkFn_10b00080
int UnkType_10b00080::UnkFn_10b00080(unsigned int Index)
{
    unsigned int i = Index % 40;
    unsigned char bFirst = unk_10[i].unk_00;
    unsigned char bSecond = unk_164[i].unk_00;
    int result = bFirst != 0;

    result |= (bSecond != 0) ? 2 : 0;
    return result;
}
