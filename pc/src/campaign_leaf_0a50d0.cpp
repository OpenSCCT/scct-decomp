// campaign_leaf_0a50d0.cpp -- one function at file offset 0xa50d0, preferred VA 0x109a50d0. It
// returns 0 when its second argument lacks bit 0x4 and its first argument has bit 0x4000 set at
// offset 0x28, when the first argument is this object, or when it has bit 0x10 set at offset 0x2c;
// otherwise the byte at offset 0x22f of the first argument, raised to at least 2, minus 2. The
// class, method and member names are invented; the offset and the bytes are the binary's.

class UnkType_109a50d0
{
public:
    unsigned char unk_0[0x28];
    int unk_28;
    int unk_2c;
    unsigned char unk_30[0x22f - 0x30];
    unsigned char unk_22f;

    int Unk_109a50d0(UnkType_109a50d0* Other, int Flags);
};

// UnkType_109a50d0::Unk_109a50d0
int UnkType_109a50d0::Unk_109a50d0(UnkType_109a50d0* Other, int Flags)
{
    if ( ( ( Flags & 4 ) || !( Other->unk_28 & 0x4000 ) ) && this != Other
        && !( Other->unk_2c & 0x10 ) )
    {
        unsigned char Value = Other->unk_22f;
        if ( Value < 2 )
        {
            Value = 2;
        }
        return Value - 2;
    }
    return 0;
}
