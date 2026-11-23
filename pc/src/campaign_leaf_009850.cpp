// campaign_leaf_009850.cpp -- method at VA 0x10909850: appends the wide string its argument points
// to to this one (character data at 0x00, count at 0x04 including the terminator): grows the count
// through the method at VA 0x10909590 by the length the free function at VA 0x10ccadc0 returns
// (plus one when this string is empty and the argument is not) and copies the characters with the
// free function at VA 0x10ccae50; returns this object. The class, member and method names are
// invented; the offsets and the addresses are the binary's.

int Unk_10ccadc0(const unsigned short* Text);
unsigned short* Unk_10ccae50(unsigned short* Dest, const unsigned short* Source);

class UnkType_10909850
{
public:
    UnkType_10909850& Unk_10909850(const unsigned short* Text);
    void Unk_10909590(int Count);

private:
    unsigned short* unk_00;
    int unk_04;
};

// UnkType_10909850::Unk_10909850
UnkType_10909850& UnkType_10909850::Unk_10909850(const unsigned short* Text)
{
    int Count = unk_04;
    if ( Count )
    {
        Unk_10909590(Unk_10ccadc0(Text));
        Unk_10ccae50(&unk_00[Count - 1], Text);
    }
    else if ( *Text )
    {
        Unk_10909590(Unk_10ccadc0(Text) + 1);
        Unk_10ccae50(unk_00, Text);
    }
    return *this;
}
