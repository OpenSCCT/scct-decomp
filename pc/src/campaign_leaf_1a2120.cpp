// campaign_leaf_1a2120.cpp -- one function at file offset 0x1a2120, preferred VA 0x10aa2120. Unless
// the flag byte at offset 0x144 is set and the float at offset 0x140 already equals the float its
// second argument points to, it records that float at offset 0x140, sets the flag, and stores it as
// the set value of the slot of the 40-entry ring at offset 0 for the word its first argument points
// to, modulo 40. It returns true. The class, method and member names are invented; the offset and
// the bytes are the binary's.

struct UnkType_10aa2120_Slot
{
    unsigned char unk_0;
    unsigned char unk_1[3];
    float unk_4;
};

class UnkType_10aa2120
{
public:
    UnkType_10aa2120_Slot unk_0[40];
    float unk_140;
    unsigned char unk_144;

    bool Unk_10aa2120(const unsigned int& Frame, const float& Value);
};

// UnkType_10aa2120::Unk_10aa2120
bool UnkType_10aa2120::Unk_10aa2120(const unsigned int& Frame, const float& Value)
{
    if ( !unk_144 || unk_140 != Value )
    {
        unk_144 = 1;
        unk_140 = Value;
        UnkType_10aa2120_Slot& Slot = unk_0[Frame % 40];
        Slot.unk_0 = 1;
        Slot.unk_4 = Value;
    }
    return true;
}
