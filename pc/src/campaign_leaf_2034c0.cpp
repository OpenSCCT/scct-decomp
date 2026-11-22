// campaign_leaf_2034c0.cpp -- one function at file offset 0x2034c0, preferred VA 0x10b034c0. It
// looks up the 8-byte slot (flag byte, value) of the 40-entry ring at offset 0x6b4 for its
// argument modulo 40; when the slot is set it copies the value to offset 0x6a8 and returns true.
// When the argument is at least 20 it clears the flag of the slot 20 entries behind. The class,
// method and member names are invented; the offset and the bytes are the binary's.

struct UnkType_10b034c0_Slot
{
    unsigned char unk_0;
    unsigned char unk_1[3];
    int unk_4;
};

class UnkType_10b034c0
{
public:
    unsigned char unk_0[0x6a8];
    int unk_6a8;
    unsigned char unk_6ac[0x6b4 - 0x6ac];
    UnkType_10b034c0_Slot unk_6b4[40];

    bool Unk_10b034c0(unsigned int Frame);
};

// UnkType_10b034c0::Unk_10b034c0
bool UnkType_10b034c0::Unk_10b034c0(unsigned int Frame)
{
    bool Result;
    UnkType_10b034c0_Slot& Slot = unk_6b4[Frame % 40];
    if ( Slot.unk_0 )
    {
        Slot.unk_0 = 1;
        unk_6a8 = Slot.unk_4;
        Result = true;
    }
    else
    {
        Result = false;
    }
    if ( Frame >= 20 )
    {
        unk_6b4[( Frame - 20 ) % 40].unk_0 = 0;
    }
    return Result;
}
