// campaign_leaf_318ef0.cpp -- one function at file offset 0x318ef0, preferred VA 0x10c18ef0. For
// each of the three 0x24-byte entries at offset 0x448 whose first two words equal its two
// arguments, it clears the second word. The class, method and member names are invented; the
// offset and the bytes are the binary's.

struct UnkType_10c18ef0_Entry
{
    int unk_0;
    int unk_4;
    unsigned char unk_8[0x24 - 0x8];
};

class UnkType_10c18ef0
{
public:
    unsigned char unk_0[0x448];
    UnkType_10c18ef0_Entry unk_448[3];

    void Unk_10c18ef0(int First, int Second);
};

// UnkType_10c18ef0::Unk_10c18ef0
void UnkType_10c18ef0::Unk_10c18ef0(int First, int Second)
{
    if ( unk_448[0].unk_0 == First && unk_448[0].unk_4 == Second )
    {
        unk_448[0].unk_4 = 0;
    }
    if ( unk_448[1].unk_0 == First && unk_448[1].unk_4 == Second )
    {
        unk_448[1].unk_4 = 0;
    }
    if ( unk_448[2].unk_0 == First && unk_448[2].unk_4 == Second )
    {
        unk_448[2].unk_4 = 0;
    }
}
