// campaign_leaf_203280.cpp -- one function at file offset 0x203280, preferred VA 0x10b03280. It
// looks up the 8-byte slot (flag byte, value) of the 40-entry ring at offset 0x40c for its
// argument modulo 40; when the slot is set it copies the value to offset 0x400 and returns true.
// When the argument is at least 20 it clears the flag of the slot 20 entries behind. The class,
// method and member names are invented; the offset and the bytes are the binary's.

struct UnkSlot
{
    unsigned char unk_0;
    unsigned char unk_1[3];
    int unk_4;
};

class UnkType_10b03280
{
public:
    unsigned char unk_0[0x400];
    int unk_400;
    unsigned char unk_404[0x40c - 0x404];
    UnkSlot unk_40c[40];

    bool Unk_10b03280(unsigned int Frame);
};

// UnkType_10b03280::Unk_10b03280
bool UnkType_10b03280::Unk_10b03280(unsigned int Frame)
{
    bool Result;
    UnkSlot& Slot = unk_40c[Frame % 40];
    if ( Slot.unk_0 )
    {
        Slot.unk_0 = 1;
        unk_400 = Slot.unk_4;
        Result = true;
    }
    else
    {
        Result = false;
    }
    if ( Frame >= 20 )
    {
        unk_40c[( Frame - 20 ) % 40].unk_0 = 0;
    }
    return Result;
}
