// campaign_leaf_203040.cpp -- one function at file offset 0x203040, preferred VA 0x10b03040. It
// looks up the 8-byte slot (flag byte, value) of the 40-entry ring at offset 0x164 for its
// argument modulo 40; when the slot is set it copies the value to offset 0x158 and returns true.
// When the argument is at least 20 it clears the flag of the slot 20 entries behind. The class,
// method and member names are invented; the offset and the bytes are the binary's.

struct UnkType_10b03040_Slot
{
    unsigned char unk_0;
    unsigned char unk_1[3];
    int unk_4;
};

class UnkType_10b03040
{
public:
    unsigned char unk_0[0x158];
    int unk_158;
    unsigned char unk_15c[0x164 - 0x15c];
    UnkType_10b03040_Slot unk_164[40];

    bool Unk_10b03040(unsigned int Frame);
};

// UnkType_10b03040::Unk_10b03040
bool UnkType_10b03040::Unk_10b03040(unsigned int Frame)
{
    bool Result;
    UnkType_10b03040_Slot& Slot = unk_164[Frame % 40];
    if ( Slot.unk_0 )
    {
        Slot.unk_0 = 1;
        unk_158 = Slot.unk_4;
        Result = true;
    }
    else
    {
        Result = false;
    }
    if ( Frame >= 20 )
    {
        unk_164[( Frame - 20 ) % 40].unk_0 = 0;
    }
    return Result;
}
