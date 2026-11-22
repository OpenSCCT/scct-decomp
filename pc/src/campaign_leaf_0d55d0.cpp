// campaign_leaf_0d55d0.cpp -- one function at file offset 0xd55d0, preferred VA 0x109d55d0. It
// stores its float argument at offset 0x18 of element i of the array at offset 0x94, when i is in
// range. The class and method names are invented; the offset and the bytes are the binary's.

struct UnkType_109d55d0_Elem
{
    unsigned char unk_00[0x0c];     // not read by these functions
    float unk_0c;
    unsigned char unk_10[0x8];      // not read by these functions
    float unk_18;
    unsigned char unk_1c[0xc];      // not read by these functions
    int unk_28;
    unsigned char unk_2c[0x54];     // not read by these functions
};

class UnkType_109d55d0
{
public:
    void UnkSetAt18(int Index, float Value);

private:
    unsigned char unk_00[0x94];     // not read by these functions
    UnkType_109d55d0_Elem *unk_94;
    int unk_98;
};

// UnkType_109d55d0::UnkSetAt18
void UnkType_109d55d0::UnkSetAt18(int Index, float Value)
{
    if ( Index >= 0 && Index < unk_98 )
    {
        unk_94[Index].unk_18 = Value;
    }
}
