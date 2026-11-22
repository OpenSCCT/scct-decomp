// campaign_leaf_4f8e00.cpp -- one function at file offset 0x4f8e00, preferred VA 0x10df8e00. When
// the halfword Id differs from the last one kept at 0x2aa (or none is kept, byte at 0x2ac clear)
// it keeps Id and marks slot Index modulo 40 of the four-byte entries at 0x20a with a set byte
// and Id. The class, method, structure, member and parameter names are invented; the offsets and
// the bytes are the binary's.

struct UnkSlot
{
    unsigned char unk_0;
    unsigned char unk_1;
    unsigned short unk_2;
};

class UnkType_10df8e00
{
public:
    void Unk_10df8e00(const unsigned short& Id, unsigned int Index);

    unsigned char unk_0[0x20a];
    UnkSlot unk_20a[40];
    unsigned short unk_2aa;
    unsigned char unk_2ac;
};

// UnkType_10df8e00::Unk_10df8e00
void UnkType_10df8e00::Unk_10df8e00(const unsigned short& Id, unsigned int Index)
{
    if ( unk_2ac == 0 || unk_2aa != Id )
    {
        UnkSlot* Slot;

        unk_2ac = 1;
        unk_2aa = Id;
        Slot = &unk_20a[Index % 40];
        Slot->unk_0 = 1;
        Slot->unk_2 = Id;
    }
}
