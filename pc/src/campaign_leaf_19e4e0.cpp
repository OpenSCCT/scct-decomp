// campaign_leaf_19e4e0.cpp -- one function at file offset 0x19e4e0, preferred VA 0x10a9e4e0.
// A constructor: after the base constructor at VA 0x10d9d560 it clears the byte at offset 0xc,
// the flags of the two 40-slot buffers at offsets 0x10 and 0x164 and the byte after each buffer,
// and the byte at offset 0x160.
// The class and member names are invented; the offset and the bytes are the binary's.

class UnkType_10a9e4e0_Base
{
public:
    unsigned char unk_0[0xc];

    UnkType_10a9e4e0_Base();
};

struct UnkType_10a9e4e0_Slot
{
    unsigned char bSet;
    int Value;

    UnkType_10a9e4e0_Slot()
        : bSet(0)
    {
    }
};

struct UnkType_10a9e4e0_History
{
    UnkType_10a9e4e0_Slot Slots[40];
    int unk_140;
    unsigned char unk_144;

    UnkType_10a9e4e0_History()
        : unk_144(0)
    {
    }
};

class UnkType_10a9e4e0 : public UnkType_10a9e4e0_Base
{
public:
    unsigned char unk_c;
    UnkType_10a9e4e0_History unk_10;
    unsigned char unk_158[0x160 - 0x158];
    unsigned char unk_160;
    UnkType_10a9e4e0_History unk_164;

    UnkType_10a9e4e0();
};

// UnkType_10a9e4e0::UnkType_10a9e4e0
UnkType_10a9e4e0::UnkType_10a9e4e0()
    : unk_c(0), unk_160(0)
{
}
