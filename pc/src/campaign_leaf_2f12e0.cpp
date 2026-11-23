// campaign_leaf_2f12e0.cpp -- method at VA 0x10bf12e0: when the byte at 0x41c is set, calls the method
// at VA 0x10a7bcb0 with the word at 0x440, 8 or 0 (8 when the object at 0x84 is set and bit 5 of its
// word at 0x2c is set) and four zeros, unless bit 1 of the word at 0x44c is set or the byte is
// already 3; then stores 3 in the byte and calls the method at VA 0x10bf04d0 with 1. The class,
// member and method names are invented; the offsets and the addresses are the binary's.

class UnkType_10bf12e0_84
{
public:
    unsigned char unk_00[0x2c];
    int unk_2c;
};

class UnkType_10bf12e0
{
public:
    void Unk_10bf12e0();
    void Unk_10a7bcb0(int Value, int Mode, int, int, int, int);
    void Unk_10bf04d0(int Flag);

private:
    unsigned char unk_00[0x84];
    UnkType_10bf12e0_84* unk_84;
    unsigned char unk_88[0x41c - 0x88];
    unsigned char unk_41c;
    unsigned char unk_41d[0x440 - 0x41d];
    int unk_440;
    unsigned char unk_444[0x44c - 0x444];
    int unk_44c;
};

// UnkType_10bf12e0::Unk_10bf12e0
void UnkType_10bf12e0::Unk_10bf12e0()
{
    if ( unk_41c )
    {
        if ( !( unk_44c & 2 ) && unk_41c != 3 )
        {
            if ( unk_84 && ( unk_84->unk_2c & 0x20 ) )
            {
                Unk_10a7bcb0(unk_440, 8, 0, 0, 0, 0);
            }
            else
            {
                Unk_10a7bcb0(unk_440, 0, 0, 0, 0, 0);
            }
        }
        unk_41c = 3;
        Unk_10bf04d0(1);
    }
}
