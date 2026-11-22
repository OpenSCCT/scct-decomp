// campaign_leaf_202eb0.cpp -- one function at file offset 0x202eb0, preferred VA 0x10b02eb0. Unless
// the flag byte at offset 0x154 is set and the float at offset 0x150 already equals the float its
// first argument points to, it records that float at offset 0x150, sets the flag, and stores it as
// the set value of the slot of the 40-entry ring at offset 0x10 for its second argument modulo 40.
// The class, method and member names are invented; the offset and the bytes are the binary's.

struct UnkSlot
{
    unsigned char unk_0;
    unsigned char unk_1[3];
    float unk_4;
};

class UnkType_10b02eb0
{
public:
    unsigned char unk_0[0x10];
    UnkSlot unk_10[40];
    float unk_150;
    unsigned char unk_154;

    void Unk_10b02eb0(const float& Value, unsigned int Frame);
};

// UnkType_10b02eb0::Unk_10b02eb0
void UnkType_10b02eb0::Unk_10b02eb0(const float& Value, unsigned int Frame)
{
    if ( !unk_154 || unk_150 != Value )
    {
        unk_154 = 1;
        unk_150 = Value;
        UnkSlot& Slot = unk_10[Frame % 40];
        Slot.unk_0 = 1;
        Slot.unk_4 = Value;
    }
}
