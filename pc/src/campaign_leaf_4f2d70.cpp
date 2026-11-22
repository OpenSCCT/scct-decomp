// campaign_leaf_4f2d70.cpp -- one function at file offset 0x4f2d70, preferred VA 0x10df2d70. When
// the halfword Id differs from the last one kept at 0xa0 (or none is kept, byte at 0xa2 clear) it
// keeps Id and marks slot Index modulo 40 of the four-byte entries at 0x0 with a set byte and
// Id. It returns true. The class, method, structure, member and parameter names are invented;
// the offsets and the bytes are the binary's.

struct UnkType_10df2d70_Slot
{
    unsigned char unk_0;
    unsigned char unk_1;
    unsigned short unk_2;
};

class UnkType_10df2d70
{
public:
    bool Unk_10df2d70(const unsigned int& Index, const unsigned short& Id);

    UnkType_10df2d70_Slot unk_0[40];
    unsigned short unk_a0;
    unsigned char unk_a2;
};

// UnkType_10df2d70::Unk_10df2d70
bool UnkType_10df2d70::Unk_10df2d70(const unsigned int& Index, const unsigned short& Id)
{
    if ( unk_a2 == 0 || unk_a0 != Id )
    {
        UnkType_10df2d70_Slot* Slot;

        unk_a2 = 1;
        unk_a0 = Id;
        Slot = &unk_0[Index % 40];
        Slot->unk_0 = 1;
        Slot->unk_2 = Id;
    }
    return true;
}
