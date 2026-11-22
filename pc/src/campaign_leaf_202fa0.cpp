// campaign_leaf_202fa0.cpp -- one function at file offset 0x202fa0, preferred VA 0x10b02fa0. Unless
// the flag byte at offset 0x2a8 is set and the float at offset 0x2a4 already equals the float its
// first argument points to, it records that float at offset 0x2a4, sets the flag, and stores it as
// the set value of the slot of the 40-entry ring at offset 0x164 for its second argument modulo 40.
// The class, method and member names are invented; the offset and the bytes are the binary's.

struct UnkSlot
{
    unsigned char unk_0;
    unsigned char unk_1[3];
    float unk_4;
};

class UnkType_10b02fa0
{
public:
    unsigned char unk_0[0x164];
    UnkSlot unk_164[40];
    float unk_2a4;
    unsigned char unk_2a8;

    void Unk_10b02fa0(const float& Value, unsigned int Frame);
};

// UnkType_10b02fa0::Unk_10b02fa0
void UnkType_10b02fa0::Unk_10b02fa0(const float& Value, unsigned int Frame)
{
    if ( !unk_2a8 || unk_2a4 != Value )
    {
        unk_2a8 = 1;
        unk_2a4 = Value;
        UnkSlot& Slot = unk_164[Frame % 40];
        Slot.unk_0 = 1;
        Slot.unk_4 = Value;
    }
}
