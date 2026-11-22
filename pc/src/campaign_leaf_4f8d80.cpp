// campaign_leaf_4f8d80.cpp -- one function at file offset 0x4f8d80, preferred VA 0x10df8d80. If
// slot Index modulo 40 of the eight-byte entries at 0xbc is marked it copies the slot's word to
// 0xb0 and returns true; either way it clears the mark of the slot twenty behind once Index has
// reached 20. The class, method, structure, member and parameter names are invented; the offsets
// and the bytes are the binary's.

struct UnkSlot
{
    unsigned char unk_0;
    unsigned char unk_1[3];
    int unk_4;
};

class UnkType_10df8d80
{
public:
    bool Unk_10df8d80(unsigned int Index);

    unsigned char unk_0[0xb0];
    int unk_b0;
    unsigned char unk_b4[0x8];
    UnkSlot unk_bc[40];
};

// UnkType_10df8d80::Unk_10df8d80
bool UnkType_10df8d80::Unk_10df8d80(unsigned int Index)
{
    UnkSlot* Slot = &unk_bc[Index % 40];
    bool Found;

    if ( Slot->unk_0 != 0 )
    {
        Slot->unk_0 = 1;
        unk_b0 = Slot->unk_4;
        Found = true;
    }
    else
    {
        Found = false;
    }
    if ( Index >= 20 )
    {
        unk_bc[( Index - 20 ) % 40].unk_0 = 0;
    }
    return Found;
}
