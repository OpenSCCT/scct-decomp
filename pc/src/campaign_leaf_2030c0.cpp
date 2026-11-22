// campaign_leaf_2030c0.cpp -- one function at file offset 0x2030c0, preferred VA 0x10b030c0. Unless
// the flag byte at offset 0x3fc is set and the float at offset 0x3f8 already equals the float its
// first argument points to, it records that float at offset 0x3f8, sets the flag, and stores it as
// the set value of the slot of the 40-entry ring at offset 0x2b8 for its second argument modulo 40.
// The class, method and member names are invented; the offset and the bytes are the binary's.

struct UnkType_10b030c0_Slot
{
    unsigned char unk_0;
    unsigned char unk_1[3];
    float unk_4;
};

class UnkType_10b030c0
{
public:
    unsigned char unk_0[0x2b8];
    UnkType_10b030c0_Slot unk_2b8[40];
    float unk_3f8;
    unsigned char unk_3fc;

    void Unk_10b030c0(const float& Value, unsigned int Frame);
};

// UnkType_10b030c0::Unk_10b030c0
void UnkType_10b030c0::Unk_10b030c0(const float& Value, unsigned int Frame)
{
    if ( !unk_3fc || unk_3f8 != Value )
    {
        unk_3fc = 1;
        unk_3f8 = Value;
        UnkType_10b030c0_Slot& Slot = unk_2b8[Frame % 40];
        Slot.unk_0 = 1;
        Slot.unk_4 = Value;
    }
}
