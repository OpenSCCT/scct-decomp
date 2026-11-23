// campaign_leaf_3e9290.cpp -- one function at file offset 0x3e9290, preferred VA 0x10ce9290. When
// Text starts with '-' or a digit it stores the number parsed by the function at 0x10ccaea0
// through Out; it then skips every '-' and digit and returns the rest of Text. It never reads
// its this pointer or its third argument. The class, method and parameter names are invented;
// the offsets and the bytes are the binary's.

int Unk_10ccaea0(const unsigned short* Text);

class UnkType_10ce9290
{
public:
    const unsigned short* Unk_10ce9290(const unsigned short* Text, int* Out, int Unused) const;
};

// UnkType_10ce9290::Unk_10ce9290
const unsigned short* UnkType_10ce9290::Unk_10ce9290(const unsigned short* Text, int* Out,
                                                     int Unused) const
{
    if ( *Text == '-' || (*Text >= '0' && *Text <= '9') )
    {
        *Out = Unk_10ccaea0(Text);
    }
    while ( *Text == '-' || (*Text >= '0' && *Text <= '9') )
    {
        Text++;
    }
    return Text;
}
