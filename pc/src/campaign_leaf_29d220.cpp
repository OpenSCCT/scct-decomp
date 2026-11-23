// campaign_leaf_29d220.cpp -- method at VA 0x10b9d220: makes two function-local static names on
// first use (L"s_Jump" and L"s_Groggy", through the name constructor at VA 0x10cd4790 with 2) and
// returns 1 when the method at VA 0x10c300f0 of the object at 0xa88 returns nonzero, this object's
// method at VA 0x10cd72b0 accepts either name, or bit 1 of the word at 0x514 is set; otherwise 0.
// The class, member and method names are invented; the offsets, the strings and the addresses are
// the binary's.

class UnkType_10b9d220_Name
{
public:
    UnkType_10b9d220_Name(const unsigned short* Text, int FindType);

private:
    int unk_00;
};

class UnkType_10b9d220_a88
{
public:
    int Unk_10c300f0();
};

class UnkType_10b9d220
{
public:
    int Unk_10b9d220();
    int Unk_10cd72b0(const UnkType_10b9d220_Name& Name);

private:
    unsigned char unk_00[0x514];
    int unk_514;
    unsigned char unk_518[0xa88 - 0x518];
    UnkType_10b9d220_a88* unk_a88;
};

// UnkType_10b9d220::Unk_10b9d220
int UnkType_10b9d220::Unk_10b9d220()
{
    static UnkType_10b9d220_Name Jump(L"s_Jump", 2);
    static UnkType_10b9d220_Name Groggy(L"s_Groggy", 2);
    if ( unk_a88->Unk_10c300f0() || Unk_10cd72b0(Jump) || Unk_10cd72b0(Groggy)
        || ( unk_514 & 2 ) )
    {
        return 1;
    }
    return 0;
}
