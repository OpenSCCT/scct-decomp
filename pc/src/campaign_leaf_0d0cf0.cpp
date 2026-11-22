// campaign_leaf_0d0cf0.cpp -- one function at file offset 0x0d0cf0, preferred VA 0x109d0cf0. When
// its first argument indexes the array of 0x80-byte entries at offset 0x94 (count at 0x98), it
// sets bit field 7 of the word at offset 0x28 of that entry from its second argument. The class,
// method and member names are invented; the offset and the bytes are the binary's.

struct UnkType_109d0cf0_Entry
{
    unsigned char unk_0[0x28];
    unsigned int unk_28_0 : 7;
    unsigned int unk_28_7 : 1;
    unsigned int unk_28_8 : 1;
    unsigned char unk_2c[0x80 - 0x2c];
};

class UnkType_109d0cf0
{
public:
    unsigned char unk_0[0x94];
    UnkType_109d0cf0_Entry* unk_94;
    int unk_98;

    void Unk_109d0cf0(int Index, int Value);
};

// UnkType_109d0cf0::Unk_109d0cf0
void UnkType_109d0cf0::Unk_109d0cf0(int Index, int Value)
{
    if ( unk_98 > Index && Index >= 0 )
    {
        unk_94[Index].unk_28_7 = Value;
    }
}
