// campaign_leaf_200000.cpp -- one leaf function at file offset 0x200000 (VA 0x10b00000).
// It takes an index into a 40-slot table of 8-byte slots at this+0x164. When the slot's flag is
// set, it sets the flag again, copies the slot's dword at +4 into this+0x158 and returns 1;
// otherwise it returns 0. Either way it then clears the flag of the slot 20 indices further on
// (when the index is 20 or more). The class, member and field names are invented; the offsets
// and the table size are the binary's.

struct UnkSlot_10b00000
{
    unsigned char unk_00;           // the flag
    unsigned char unk_01[3];        // not read by this function
    unsigned int unk_04;
};

class UnkType_10b00000
{
public:
    unsigned char UnkFn_10b00000(unsigned int Index);

private:
    unsigned char unk_00[0x158];    // not read by this function
    unsigned int unk_158;
    unsigned char unk_15c[8];       // not read by this function
    UnkSlot_10b00000 unk_164[40];
};

// UnkType_10b00000::UnkFn_10b00000
unsigned char UnkType_10b00000::UnkFn_10b00000(unsigned int Index)
{
    unsigned char bResult;
    UnkSlot_10b00000 *pSlot = &unk_164[Index % 40];

    if (pSlot->unk_00 != 0) {
        pSlot->unk_00 = 1;
        unk_158 = pSlot->unk_04;
        bResult = 1;
    } else {
        bResult = 0;
    }
    if (Index >= 20) {
        unk_164[(Index - 20) % 40].unk_00 = 0;
    }
    return bResult;
}
