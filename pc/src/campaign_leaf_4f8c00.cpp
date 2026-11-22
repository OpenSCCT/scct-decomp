// campaign_leaf_4f8c00.cpp -- one function at file offset 0x4f8c00, preferred VA 0x10df8c00. When
// the halfword Id differs from the last one kept at 0xaa (or none is kept, byte at 0xac clear) it
// keeps Id and marks slot Index modulo 40 of the four-byte entries at 0xa with a set byte and
// Id. The class, method, structure, member and parameter names are invented; the offsets and the
// bytes are the binary's.

struct UnkType_10df8c00_Slot
{
    unsigned char unk_0;
    unsigned char unk_1;
    unsigned short unk_2;
};

class UnkType_10df8c00
{
public:
    void Unk_10df8c00(const unsigned short& Id, unsigned int Index);

    unsigned char unk_0[0xa];
    UnkType_10df8c00_Slot unk_a[40];
    unsigned short unk_aa;
    unsigned char unk_ac;
};

// UnkType_10df8c00::Unk_10df8c00
void UnkType_10df8c00::Unk_10df8c00(const unsigned short& Id, unsigned int Index)
{
    if ( unk_ac == 0 || unk_aa != Id )
    {
        UnkType_10df8c00_Slot* Slot;

        unk_ac = 1;
        unk_aa = Id;
        Slot = &unk_a[Index % 40];
        Slot->unk_0 = 1;
        Slot->unk_2 = Id;
    }
}
