// campaign_leaf_203300.cpp -- one function at file offset 0x203300, preferred VA 0x10b03300. Unless
// the flag byte at offset 0x6a4 is set and the float at offset 0x6a0 already equals the float its
// first argument points to, it records that float at offset 0x6a0, sets the flag, and stores it as
// the set value of the slot of the 40-entry ring at offset 0x560 for its second argument modulo 40.
// The class, method and member names are invented; the offset and the bytes are the binary's.

struct UnkType_10b03300_Slot
{
    unsigned char unk_0;
    unsigned char unk_1[3];
    float unk_4;
};

class UnkType_10b03300
{
public:
    unsigned char unk_0[0x560];
    UnkType_10b03300_Slot unk_560[40];
    float unk_6a0;
    unsigned char unk_6a4;

    void Unk_10b03300(const float& Value, unsigned int Frame);
};

// UnkType_10b03300::Unk_10b03300
void UnkType_10b03300::Unk_10b03300(const float& Value, unsigned int Frame)
{
    if ( !unk_6a4 || unk_6a0 != Value )
    {
        unk_6a4 = 1;
        unk_6a0 = Value;
        UnkType_10b03300_Slot& Slot = unk_560[Frame % 40];
        Slot.unk_0 = 1;
        Slot.unk_4 = Value;
    }
}
