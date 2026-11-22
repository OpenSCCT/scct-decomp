// campaign_leaf_2031e0.cpp -- one function at file offset 0x2031e0, preferred VA 0x10b031e0. Unless
// the flag byte at offset 0x550 is set and the float at offset 0x54c already equals the float its
// first argument points to, it records that float at offset 0x54c, sets the flag, and stores it as
// the set value of the slot of the 40-entry ring at offset 0x40c for its second argument modulo 40.
// The class, method and member names are invented; the offset and the bytes are the binary's.

struct UnkType_10b031e0_Slot
{
    unsigned char unk_0;
    unsigned char unk_1[3];
    float unk_4;
};

class UnkType_10b031e0
{
public:
    unsigned char unk_0[0x40c];
    UnkType_10b031e0_Slot unk_40c[40];
    float unk_54c;
    unsigned char unk_550;

    void Unk_10b031e0(const float& Value, unsigned int Frame);
};

// UnkType_10b031e0::Unk_10b031e0
void UnkType_10b031e0::Unk_10b031e0(const float& Value, unsigned int Frame)
{
    if ( !unk_550 || unk_54c != Value )
    {
        unk_550 = 1;
        unk_54c = Value;
        UnkType_10b031e0_Slot& Slot = unk_40c[Frame % 40];
        Slot.unk_0 = 1;
        Slot.unk_4 = Value;
    }
}
