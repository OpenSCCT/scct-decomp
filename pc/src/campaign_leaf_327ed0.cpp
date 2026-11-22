// campaign_leaf_327ed0.cpp -- one function at file offset 0x327ed0, preferred VA 0x10c27ed0. It
// counts the 8-byte entries of the array at offset 0x88 (count at 0x8c) whose first byte equals
// its argument. The class, method and member names are invented; the offset and the bytes are the
// binary's.

struct UnkEntry_10c27ed0
{
    unsigned char unk_0;
    unsigned char unk_1[7];
};

class UnkType_10c27ed0
{
public:
    unsigned char unk_0[0x88];
    UnkEntry_10c27ed0* unk_88;
    int unk_8c;

    int Unk_10c27ed0(int Value);
};

// UnkType_10c27ed0::Unk_10c27ed0
int UnkType_10c27ed0::Unk_10c27ed0(int Value)
{
    int Count = 0;
    for ( int i = 0; i < unk_8c; i++ )
    {
        if ( unk_88[i].unk_0 == Value )
        {
            Count++;
        }
    }
    return Count;
}
