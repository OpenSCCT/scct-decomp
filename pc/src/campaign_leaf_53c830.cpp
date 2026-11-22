// campaign_leaf_53c830.cpp -- one function at file offset 0x53c830, preferred VA 0x10e3c830. It
// copies From's word at 0x34 to To, then replaces it with Source's word at 0x24 when the grown
// size (To's word at 0x38, less From's word at 0x34, plus that word) reaches 0x20, and 0x100
// when To's size is at most 2, and To's size is below one of the limits 0x20, 0x100 and 0x10000
// that From's size at 0x38 reaches. It never reads its this pointer. The class, method,
// structure, member and parameter names are invented; the offsets and the bytes are the
// binary's.

struct UnkType_10e3c830_Source
{
    unsigned char unk_0[0x24];
    unsigned int unk_24;
};

struct UnkType_10e3c830_Range
{
    unsigned char unk_0[0x34];
    unsigned int unk_34;
    unsigned int unk_38;
};

class UnkType_10e3c830
{
public:
    void Unk_10e3c830(const UnkType_10e3c830_Source& Source, const UnkType_10e3c830_Range& From,
                      UnkType_10e3c830_Range& To) const;
};

// UnkType_10e3c830::Unk_10e3c830
void UnkType_10e3c830::Unk_10e3c830(const UnkType_10e3c830_Source& Source,
                                    const UnkType_10e3c830_Range& From,
                                    UnkType_10e3c830_Range& To) const
{
    unsigned int Extra;
    unsigned int Size;
    unsigned int Total;

    To.unk_34 = From.unk_34;
    Extra = Source.unk_24;
    Size = To.unk_38;
    Total = Size - From.unk_34 + Extra;
    if ( Total < 0x20 )
    {
        return;
    }
    if ( Size <= 2 && Total < 0x100 )
    {
        return;
    }
    if ( (Size < 0x20 && From.unk_38 >= 0x20) || (Size < 0x100 && From.unk_38 >= 0x100)
        || (Size < 0x10000 && From.unk_38 >= 0x10000) )
    {
        To.unk_34 = Extra;
    }
}
