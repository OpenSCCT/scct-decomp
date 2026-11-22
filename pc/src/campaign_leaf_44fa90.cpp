// campaign_leaf_44fa90.cpp -- one function at file offset 0x44fa90, preferred VA 0x10d4fa90. It
// looks a sixteen-bit code up in a two-level table: the high byte picks a page pointer at 0x0,
// the low byte a halfword in that page; a missing page gives 0. The class, method, member and
// parameter names are invented; the offsets and the bytes are the binary's.

class UnkType_10d4fa90
{
public:
    unsigned short Unk_10d4fa90(unsigned short Code) const;

    unsigned short* unk_0[256];
};

// UnkType_10d4fa90::Unk_10d4fa90
unsigned short UnkType_10d4fa90::Unk_10d4fa90(unsigned short Code) const
{
    unsigned short* Page = unk_0[(unsigned char)( Code >> 8 )];

    if ( Page == 0 )
    {
        return 0;
    }
    return Page[Code % 256];
}
