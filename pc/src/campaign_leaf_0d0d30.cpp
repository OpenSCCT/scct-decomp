// campaign_leaf_0d0d30.cpp -- one function at file offset 0xd0d30, preferred VA 0x109d0d30. It
// sets bit 9 of the word at offset 0x28 of element i of the array at offset 0x94, when i is in
// range. The class and method names are invented; the offset and the bytes are the binary's.

struct UnkType_109d0d30_Elem
{
    unsigned char unk_00[0x0c];     // not read by these functions
    float unk_0c;
    unsigned char unk_10[0x8];      // not read by these functions
    float unk_18;
    unsigned char unk_1c[0xc];      // not read by these functions
    int unk_28;
    unsigned char unk_2c[0x54];     // not read by these functions
};

class UnkType_109d0d30
{
public:
    void UnkSetBit9(int Index);

private:
    unsigned char unk_00[0x94];     // not read by these functions
    UnkType_109d0d30_Elem *unk_94;
    int unk_98;
};

// UnkType_109d0d30::UnkSetBit9
void UnkType_109d0d30::UnkSetBit9(int Index)
{
    if ( unk_98 > Index && Index >= 0 )
    {
        unk_94[Index].unk_28 |= 0x200;
    }
}
