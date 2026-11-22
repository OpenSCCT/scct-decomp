// campaign_leaf_2d9f10.cpp -- one function at file offset 0x2d9f10, preferred VA 0x10bd9f10. It
// returns 1 when the byte array at offset 0x3d8 (count at 0x3dc) contains its argument, else 0.
// The class, method and member names are invented; the offset and the bytes are the binary's.

class UnkType_10bd9f10
{
public:
    unsigned char unk_0[0x3d8];
    unsigned char* unk_3d8;
    int unk_3dc;

    int Unk_10bd9f10(int Value);
};

// UnkType_10bd9f10::Unk_10bd9f10
int UnkType_10bd9f10::Unk_10bd9f10(int Value)
{
    for ( int i = 0; i < unk_3dc; i++ )
    {
        if ( unk_3d8[i] == Value )
        {
            return 1;
        }
    }
    return 0;
}
