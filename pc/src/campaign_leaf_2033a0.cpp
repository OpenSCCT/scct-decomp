// campaign_leaf_2033a0.cpp -- one function at file offset 0x2033a0, preferred VA 0x10b033a0. It
// looks up the 8-byte slot (flag byte, value) of the 40-entry ring at offset 0x560 for its
// argument modulo 40; when the slot is set it copies the value to offset 0x554 and returns true.
// When the argument is at least 20 it clears the flag of the slot 20 entries behind. The class,
// method and member names are invented; the offset and the bytes are the binary's.

struct UnkType_10b033a0_Slot
{
    unsigned char unk_0;
    unsigned char unk_1[3];
    int unk_4;
};

class UnkType_10b033a0
{
public:
    unsigned char unk_0[0x554];
    int unk_554;
    unsigned char unk_558[0x560 - 0x558];
    UnkType_10b033a0_Slot unk_560[40];

    bool Unk_10b033a0(unsigned int Frame);
};

// UnkType_10b033a0::Unk_10b033a0
bool UnkType_10b033a0::Unk_10b033a0(unsigned int Frame)
{
    bool Result;
    UnkType_10b033a0_Slot& Slot = unk_560[Frame % 40];
    if ( Slot.unk_0 )
    {
        Slot.unk_0 = 1;
        unk_554 = Slot.unk_4;
        Result = true;
    }
    else
    {
        Result = false;
    }
    if ( Frame >= 20 )
    {
        unk_560[( Frame - 20 ) % 40].unk_0 = 0;
    }
    return Result;
}
