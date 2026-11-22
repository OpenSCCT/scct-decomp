// campaign_band2_short_fields.cpp -- getters for three 16-bit fields at offsets 4, 6 and 8, from
// the functions at VA 0x10dc8070, 0x10dc8080 and 0x10dc80a0. The word getter between them, at
// VA 0x10dc8090, is matched elsewhere. The class and method names are invented; the offsets are
// the binary's.

class UnkType_10dc8070
{
public:
    unsigned short GetUnk04();
    unsigned short GetUnk06();
    unsigned short GetUnk08();

private:
    unsigned char unk_00[4];        // not read by any function in this unit
    unsigned short unk_04;
    unsigned short unk_06;
    unsigned short unk_08;
};

// UnkType_10dc8070::GetUnk04
unsigned short UnkType_10dc8070::GetUnk04()
{
    return unk_04;
}

// UnkType_10dc8070::GetUnk06
unsigned short UnkType_10dc8070::GetUnk06()
{
    return unk_06;
}

// UnkType_10dc8070::GetUnk08
unsigned short UnkType_10dc8070::GetUnk08()
{
    return unk_08;
}
