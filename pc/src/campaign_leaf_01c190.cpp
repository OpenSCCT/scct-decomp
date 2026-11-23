// campaign_leaf_01c190.cpp -- method at VA 0x1091c190: appends a backslash to this string (its
// characters at 0x00, count at 0x04 including the terminator) through the method at VA 0x10909850
// unless it is empty or already ends in one, then appends the string its argument points to the
// same way. The class, member and method names are invented; the offsets and the address are the
// binary's.

class UnkType_1091c190
{
public:
    void Unk_1091c190(const unsigned short* Text);
    UnkType_1091c190& Unk_10909850(const unsigned short* Text);

private:
    unsigned short* unk_00;
    int unk_04;
};

// UnkType_1091c190::Unk_1091c190
void UnkType_1091c190::Unk_1091c190(const unsigned short* Text)
{
    if ( unk_04 > 1 && unk_00[unk_04 - 2] != '\\' )
    {
        Unk_10909850(L"\\");
    }
    Unk_10909850(Text);
}
