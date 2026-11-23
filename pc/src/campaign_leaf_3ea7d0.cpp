// campaign_leaf_3ea7d0.cpp -- one function at file offset 0x3ea7d0, preferred VA 0x10cea7d0. It
// writes the text of Value (data at 0x0, count at 0x4, an empty string when the count is zero)
// to Out: copied through the function at 0x10ccae50, or, when bit 1 of Flags is set, formatted in
// quotes through the function at 0x10ccb0d0 with the retail format "\"%s\"". It never reads its
// this pointer. The class, function, structure, member and parameter names are invented; the
// offsets, the format and the bytes are the binary's.

unsigned short* Unk_10ccae50(unsigned short* Out, const unsigned short* Text);
int Unk_10ccb0d0(unsigned short* Out, const unsigned short* Format, ...);

struct UnkType_10cea7d0_String
{
    unsigned short* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10cea7d0
{
public:
    void Unk_10cea7d0(unsigned short* Out, const UnkType_10cea7d0_String* Value,
                      const UnkType_10cea7d0_String* Default, int Flags);
};

// UnkType_10cea7d0::Unk_10cea7d0
void UnkType_10cea7d0::Unk_10cea7d0(unsigned short* Out, const UnkType_10cea7d0_String* Value,
                                    const UnkType_10cea7d0_String* Default, int Flags)
{
    if ( !(Flags & 2) )
    {
        Unk_10ccae50(Out, Value->unk_4 ? Value->unk_0 : L"");
    }
    else
    {
        Unk_10ccb0d0(Out, L"\"%s\"", Value->unk_4 ? Value->unk_0 : L"");
    }
}
