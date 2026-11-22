// campaign_leaf_12b560.cpp -- returns bit 0 of the dword at offset 0x18 of entry Index, where the
// entries are 0x1c bytes each and the array is at offset 0x34 of this. File offset 0x12b560, VA
// 0x10a2b560. The class and method names are invented; the offsets are the binary's, and the
// element type is a guess.

class UnkEntry_10a2b560;

class UnkType_10a2b560
{
public:
    int GetUnk34Entry18Bit0(int Index);

private:
    unsigned char unk_00[0x34];     // not read by this function
    UnkEntry_10a2b560 *unk_34;      // guess: array of entries
};

class UnkEntry_10a2b560
{
public:
    unsigned char unk_00[0x18];     // not read by this function
    int unk_18;
};

// UnkType_10a2b560::GetUnk34Entry18Bit0
int UnkType_10a2b560::GetUnk34Entry18Bit0(int Index)
{
    return unk_34[Index].unk_18 & 1;
}
