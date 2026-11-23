// campaign_leaf_763030.cpp -- one function at file offset 0x763030, preferred VA 0x11063030. It
// copies into the block it is given the 0x18-byte block that the static method at VA 0x110570f0
// of the object returned by the function at VA 0x11056900 finds for the record. When the record's
// kind at 0x4 is 1 it then stores the differences of the words at 0x48 and 0x24 and at 0x4c and
// 0x28 at 0x10 and 0x14, and adds the word at 0x24 to the word at 0x8 when the record's word at
// 0x38 is set, to the word at 0x4 otherwise. The type and function names are invented; the
// offsets and the addresses are the binary's.

struct UnkType_11063030_Block
{
    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;
    int unk_10;
    int unk_14;
};

struct UnkType_11063030_Record
{
    int unk_0;
    int unk_4;
    unsigned char unk_8[0x24 - 0x8];
    int unk_24;
    int unk_28;
    unsigned char unk_2c[0x38 - 0x2c];
    int unk_38;
    unsigned char unk_3c[0x48 - 0x3c];
    int unk_48;
    int unk_4c;
};

class UnkType_11063030_Source
{
public:
    static UnkType_11063030_Block* Unk_110570f0(UnkType_11063030_Record* Record);
};

UnkType_11063030_Source* Unk_11056900();

// Unk_11063030
void Unk_11063030(UnkType_11063030_Block* Block, UnkType_11063030_Record* Record)
{
    *Block = *Unk_11056900()->Unk_110570f0(Record);
    if ( Record->unk_4 == 1 )
    {
        Block->unk_10 = Record->unk_48 - Record->unk_24;
        Block->unk_14 = Record->unk_4c - Record->unk_28;
        if ( Record->unk_38 != 0 )
        {
            Block->unk_8 += Record->unk_24;
        }
        else
        {
            Block->unk_4 += Record->unk_24;
        }
    }
}
