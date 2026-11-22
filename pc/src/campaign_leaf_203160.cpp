// campaign_leaf_203160.cpp -- one function at file offset 0x203160, preferred VA 0x10b03160. It
// looks up the 8-byte slot (flag byte, value) of the 40-entry ring at offset 0x2b8 for its
// argument modulo 40; when the slot is set it copies the value to offset 0x2ac and returns true.
// When the argument is at least 20 it clears the flag of the slot 20 entries behind. The class,
// method and member names are invented; the offset and the bytes are the binary's.

struct UnkType_10b03160_Slot
{
    unsigned char unk_0;
    unsigned char unk_1[3];
    int unk_4;
};

class UnkType_10b03160
{
public:
    unsigned char unk_0[0x2ac];
    int unk_2ac;
    unsigned char unk_2b0[0x2b8 - 0x2b0];
    UnkType_10b03160_Slot unk_2b8[40];

    bool Unk_10b03160(unsigned int Frame);
};

// UnkType_10b03160::Unk_10b03160
bool UnkType_10b03160::Unk_10b03160(unsigned int Frame)
{
    bool Result;
    UnkType_10b03160_Slot& Slot = unk_2b8[Frame % 40];
    if ( Slot.unk_0 )
    {
        Slot.unk_0 = 1;
        unk_2ac = Slot.unk_4;
        Result = true;
    }
    else
    {
        Result = false;
    }
    if ( Frame >= 20 )
    {
        unk_2b8[( Frame - 20 ) % 40].unk_0 = 0;
    }
    return Result;
}
