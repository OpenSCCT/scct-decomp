// campaign_leaf_364140.cpp -- one function at file offset 0x364140, preferred VA 0x10c64140. It
// builds a function-local static name once from the retail string "s_CoopTeamShouldersSecondary"
// and 2 (constructor at 0x10cd4790); when the method at 0x10cd72b0 of Other accepts that name it
// passes Other to the method at 0x10c045b0 and clears Other's word at 0x988, otherwise it passes
// Other to the method at 0x10c55870. The class, method, member, local and parameter names are
// invented; the offsets, the string and the bytes are the binary's.

class UnkType_10c64140_Name
{
public:
    UnkType_10c64140_Name(const unsigned short* Text, int Flags);

    int unk_0;
};

class UnkType_10c64140_Other
{
public:
    int Unk_10cd72b0(const UnkType_10c64140_Name& Name);

    unsigned char unk_0[0x988];
    int unk_988;
};

class UnkType_10c64140
{
public:
    void Unk_10c045b0(UnkType_10c64140_Other* Other);
    void Unk_10c55870(UnkType_10c64140_Other* Other);
    void Unk_10c64140(UnkType_10c64140_Other* Other);
};

// UnkType_10c64140::Unk_10c64140
void UnkType_10c64140::Unk_10c64140(UnkType_10c64140_Other* Other)
{
    static UnkType_10c64140_Name ShouldersName(L"s_CoopTeamShouldersSecondary", 2);
    if ( Other->Unk_10cd72b0(ShouldersName) )
    {
        Unk_10c045b0(Other);
        Other->unk_988 = 0;
    }
    else
    {
        Unk_10c55870(Other);
    }
}
