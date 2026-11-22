// campaign_leaf_4f8cf0.cpp -- one function at file offset 0x4f8cf0, preferred VA 0x10df8cf0. When
// the word Id differs from the last one kept at 0x1fc (or none is kept, byte at 0x200 clear) it
// keeps Id and marks slot Index modulo 40 of the eight-byte entries at 0xbc with a set byte and
// Id. The class, method, structure, member and parameter names are invented; the offsets and the
// bytes are the binary's.

struct UnkType_10df8cf0_Slot
{
    unsigned char unk_0;
    unsigned char unk_1[3];
    int unk_4;
};

class UnkType_10df8cf0
{
public:
    void Unk_10df8cf0(const int& Id, unsigned int Index);

    unsigned char unk_0[0xbc];
    UnkType_10df8cf0_Slot unk_bc[40];
    int unk_1fc;
    unsigned char unk_200;
};

// UnkType_10df8cf0::Unk_10df8cf0
void UnkType_10df8cf0::Unk_10df8cf0(const int& Id, unsigned int Index)
{
    if ( unk_200 == 0 || unk_1fc != Id )
    {
        UnkType_10df8cf0_Slot* Slot;

        unk_200 = 1;
        unk_1fc = Id;
        Slot = &unk_bc[Index % 40];
        Slot->unk_0 = 1;
        Slot->unk_4 = Id;
    }
}
