// campaign_leaf_4f8ea0.cpp -- one function at file offset 0x4f8ea0, preferred VA 0x10df8ea0. If
// slot Index modulo 40 of the four-byte entries at 0x20a is marked it copies the slot's halfword
// to 0x204 and returns true; either way it clears the mark of the slot twenty behind once Index
// has reached 20. The class, method, structure, member and parameter names are invented; the
// offsets and the bytes are the binary's.

struct UnkSlot
{
    unsigned char unk_0;
    unsigned char unk_1;
    unsigned short unk_2;
};

class UnkType_10df8ea0
{
public:
    bool Unk_10df8ea0(unsigned int Index);

    unsigned char unk_0[0x204];
    unsigned short unk_204;
    unsigned char unk_206[0x4];
    UnkSlot unk_20a[40];
};

// UnkType_10df8ea0::Unk_10df8ea0
bool UnkType_10df8ea0::Unk_10df8ea0(unsigned int Index)
{
    UnkSlot* Slot = &unk_20a[Index % 40];
    bool Found;

    if ( Slot->unk_0 != 0 )
    {
        Slot->unk_0 = 1;
        unk_204 = Slot->unk_2;
        Found = true;
    }
    else
    {
        Found = false;
    }
    if ( Index >= 20 )
    {
        unk_20a[( Index - 20 ) % 40].unk_0 = 0;
    }
    return Found;
}
