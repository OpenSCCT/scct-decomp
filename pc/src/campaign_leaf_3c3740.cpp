// campaign_leaf_3c3740.cpp -- one function at file offset 0x3c3740, preferred VA 0x10cc3740. It
// translates bits 0, 1, 4, 5 and 6 of Flags, and the low bits of the three bytes at 0xf8c to
// 0xf8e of the object at 0x5c, into another flag word. The class, method, structure, member and
// parameter names are invented; the offsets and the bytes are the binary's.

struct UnkType_10cc3740_Owner
{
    unsigned char unk_0[0xf8c];
    unsigned char unk_f8c;
    unsigned char unk_f8d;
    unsigned char unk_f8e;
};

class UnkType_10cc3740
{
public:
    int Unk_10cc3740(unsigned char Flags) const;

    unsigned char unk_0[0x5c];
    UnkType_10cc3740_Owner* unk_5c;
};

// UnkType_10cc3740::Unk_10cc3740
int UnkType_10cc3740::Unk_10cc3740(unsigned char Flags) const
{
    int Used = Flags & 0x73;
    int Result = 0;

    if ( Used & 0x01 )
    {
        Result = 0x0001;
    }
    if ( Used & 0x02 )
    {
        Result |= 0x0002;
    }
    if ( Used & 0x10 )
    {
        Result |= 0x0004;
    }
    if ( Used & 0x20 )
    {
        Result |= 0x2000;
    }
    if ( Used & 0x40 )
    {
        Result |= 0x4000;
    }
    if ( unk_5c->unk_f8c & 1 )
    {
        Result |= 0x0100;
    }
    if ( unk_5c->unk_f8d & 1 )
    {
        Result |= 0x0080;
    }
    if ( unk_5c->unk_f8e & 1 )
    {
        Result |= 0x0200;
    }
    return Result;
}
