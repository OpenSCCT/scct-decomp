// campaign_leaf_2bc280.cpp -- method at VA 0x10bbc280: makes a function-local static name
// L"s_Following" on first use (through the name constructor at VA 0x10cd4790 with 2) and returns 1
// when the object at 0x7c0 is set and its method at VA 0x10cd72b0 accepts that name, otherwise 0.
// The class, member and method names are invented; the offset, the string and the addresses are the
// binary's.

class UnkType_10bbc280_Name
{
public:
    UnkType_10bbc280_Name(const unsigned short* Text, int FindType);

private:
    int unk_00;
};

class UnkType_10bbc280_7c0
{
public:
    int Unk_10cd72b0(const UnkType_10bbc280_Name& Name);
};

class UnkType_10bbc280
{
public:
    int Unk_10bbc280();

private:
    unsigned char unk_00[0x7c0];
    UnkType_10bbc280_7c0* unk_7c0;
};

// UnkType_10bbc280::Unk_10bbc280
int UnkType_10bbc280::Unk_10bbc280()
{
    static UnkType_10bbc280_Name Following(L"s_Following", 2);
    if ( unk_7c0 && unk_7c0->Unk_10cd72b0(Following) )
    {
        return 1;
    }
    return 0;
}
