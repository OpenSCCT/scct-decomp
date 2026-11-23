// campaign_leaf_3eb0b0.cpp -- one function at file offset 0x3eb0b0, preferred VA 0x10ceb0b0. It
// formats the byte Value to Out through the function at 0x10ccb0d0: with the object at 0x54 set,
// as the text of that object's name entry Value (names at 0x34, count at 0x38, text through the
// method at 0x10907e60) or the retail "(INVALID)" when Value is out of range, under "%s";
// without it, as a number under "%i". It never reads Default or Flags. The class, function,
// method, member and parameter names are invented; the offsets, the strings and the bytes are
// the binary's.

int Unk_10ccb0d0(unsigned short* Out, const unsigned short* Format, ...);

class UnkType_10ceb0b0_Name
{
public:
    const unsigned short* Unk_10907e60() const;

    int unk_0;
};

class UnkType_10ceb0b0_Names
{
public:
    unsigned char unk_0[0x34];
    UnkType_10ceb0b0_Name* unk_34;
    int unk_38;
};

class UnkType_10ceb0b0
{
public:
    void Unk_10ceb0b0(unsigned short* Out, const unsigned char* Value, const unsigned char* Default,
                      int Flags);

    unsigned char unk_0[0x54];
    UnkType_10ceb0b0_Names* unk_54;
};

// UnkType_10ceb0b0::Unk_10ceb0b0
void UnkType_10ceb0b0::Unk_10ceb0b0(unsigned short* Out, const unsigned char* Value,
                                    const unsigned char* Default, int Flags)
{
    if ( unk_54 != 0 )
    {
        Unk_10ccb0d0(Out, L"%s", *Value < unk_54->unk_38 ? unk_54->unk_34[*Value].Unk_10907e60()
                                                         : L"(INVALID)");
    }
    else
    {
        Unk_10ccb0d0(Out, L"%i", *Value);
    }
}
