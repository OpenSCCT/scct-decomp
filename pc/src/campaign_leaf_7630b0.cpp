// campaign_leaf_7630b0.cpp -- one function at file offset 0x7630b0, preferred VA 0x110630b0. It
// copies the 0x18-byte block that the static method at VA 0x110570f0 of the object returned by
// the function at VA 0x11056900 finds for the record into the first argument; when the record's
// word at 0x4 is 1 it then stores the record's words at 0x24 and 0x28 at 0x10 and 0x14 of the
// copy, and otherwise clears them. The type and function names are invented; the offsets and
// the addresses are the binary's.

struct UnkType_110630b0_Block
{
    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;
    int unk_10;
    int unk_14;
};

struct UnkType_110630b0_Record
{
    int unk_0;
    int unk_4;
    unsigned char unk_8[0x24 - 0x8];
    int unk_24;
    int unk_28;
};

class UnkType_110630b0_Manager
{
public:
    static UnkType_110630b0_Block* Unk_110570f0(UnkType_110630b0_Record* Record);
};

UnkType_110630b0_Manager* Unk_11056900();

// Unk_110630b0
void Unk_110630b0(UnkType_110630b0_Block* Block, UnkType_110630b0_Record* Record)
{
    *Block = *Unk_11056900()->Unk_110570f0(Record);
    if ( Record->unk_4 == 1 )
    {
        Block->unk_10 = Record->unk_24;
        Block->unk_14 = Record->unk_28;
    }
    else
    {
        Block->unk_10 = 0;
        Block->unk_14 = 0;
    }
}
