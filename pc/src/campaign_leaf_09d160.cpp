// campaign_leaf_09d160.cpp -- one function at file offset 0x9d160, preferred VA 0x1099d160. It
// returns 0 when its first argument has bit 0x10 set at offset 0x2c or is the object stored at
// offset 0x6c of this one; otherwise the byte at offset 0x230 of the argument, raised to at least
// 2, minus 2. Its second argument is never read. The class, method and member names are
// invented; the offset and the bytes are the binary's.

class UnkType_1099d160
{
public:
    unsigned char unk_0[0x2c];
    int unk_2c;
    unsigned char unk_30[0x6c - 0x30];
    UnkType_1099d160* unk_6c;
    unsigned char unk_70[0x230 - 0x70];
    unsigned char unk_230;

    int Unk_1099d160(UnkType_1099d160* Other, int Unused);
};

// UnkType_1099d160::Unk_1099d160
int UnkType_1099d160::Unk_1099d160(UnkType_1099d160* Other, int Unused)
{
    if ( !( Other->unk_2c & 0x10 ) && Other != unk_6c )
    {
        unsigned char Value = Other->unk_230;
        if ( Value < 2 )
        {
            Value = 2;
        }
        return Value - 2;
    }
    return 0;
}
