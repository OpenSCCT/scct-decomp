// campaign_leaf_203420.cpp -- one function at file offset 0x203420, preferred VA 0x10b03420. Unless
// the flag byte at offset 0x7f8 is set and the float at offset 0x7f4 already equals the float its
// first argument points to, it records that float at offset 0x7f4, sets the flag, and stores it as
// the set value of the slot of the 40-entry ring at offset 0x6b4 for its second argument modulo 40.
// The class, method and member names are invented; the offset and the bytes are the binary's.

struct UnkType_10b03420_Slot
{
    unsigned char unk_0;
    unsigned char unk_1[3];
    float unk_4;
};

class UnkType_10b03420
{
public:
    unsigned char unk_0[0x6b4];
    UnkType_10b03420_Slot unk_6b4[40];
    float unk_7f4;
    unsigned char unk_7f8;

    void Unk_10b03420(const float& Value, unsigned int Frame);
};

// UnkType_10b03420::Unk_10b03420
void UnkType_10b03420::Unk_10b03420(const float& Value, unsigned int Frame)
{
    if ( !unk_7f8 || unk_7f4 != Value )
    {
        unk_7f8 = 1;
        unk_7f4 = Value;
        UnkType_10b03420_Slot& Slot = unk_6b4[Frame % 40];
        Slot.unk_0 = 1;
        Slot.unk_4 = Value;
    }
}
