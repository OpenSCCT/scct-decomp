// campaign_leaf_2f2f80.cpp -- method at VA 0x10bf2f80: makes a function-local static name L"s_On"
// on first use (through the name constructor at VA 0x10cd4790 with 2); returns 0 when bit 0 of the
// word at 0x40c is set, the object at 0x6c is set and the name its method at VA 0x10cee180 returns
// differs from that one; otherwise returns what the method at VA 0x10be9a30 returns. The class,
// member and method names are invented; the offsets, the string and the addresses are the binary's.

class UnkType_10bf2f80_Name
{
public:
    UnkType_10bf2f80_Name(const unsigned short* Text, int FindType);

    int operator!=(const UnkType_10bf2f80_Name& Other) const
    {
        return unk_00 != Other.unk_00;
    }

private:
    int unk_00;
};

class UnkType_10bf2f80_6c
{
public:
    UnkType_10bf2f80_Name Unk_10cee180();
};

class UnkType_10bf2f80
{
public:
    int Unk_10bf2f80();
    int Unk_10be9a30();

private:
    unsigned char unk_00[0x6c];
    UnkType_10bf2f80_6c* unk_6c;
    unsigned char unk_70[0x40c - 0x70];
    int unk_40c;
};

// UnkType_10bf2f80::Unk_10bf2f80
int UnkType_10bf2f80::Unk_10bf2f80()
{
    static UnkType_10bf2f80_Name On(L"s_On", 2);
    if ( ( unk_40c & 1 ) && unk_6c && unk_6c->Unk_10cee180() != On )
    {
        return 0;
    }
    return Unk_10be9a30();
}
