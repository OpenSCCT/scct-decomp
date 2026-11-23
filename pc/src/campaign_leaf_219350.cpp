// campaign_leaf_219350.cpp -- a member function at VA 0x10b19350 that walks the 0x84-byte entries
// at 0x1914 (count in the signed byte at 0x1b25), passing each entry and its 16-bit value at 0x82
// to the function at VA 0x10ee83d0 until one returns true; it then sets the int at 0x16fc to 4 when
// one did, otherwise to 0. The class, function, method and member names are invented; the offsets,
// sizes, constants and addresses are the binary's.

class UnkType_10b19350_Entry
{
public:
    unsigned char unk_00[0x82];
    unsigned short unk_82;
};

bool __stdcall Unk_10ee83d0(UnkType_10b19350_Entry* Entry, unsigned short Value);

class UnkType_10b19350
{
public:
    void Unk_10b19350();

private:
    unsigned char unk_0000[0x16fc];
    int unk_16fc;
    unsigned char unk_1700[0x1914 - 0x1700];
    UnkType_10b19350_Entry unk_1914[4];
    unsigned char unk_1b24;
    signed char unk_1b25;
};

// UnkType_10b19350::Unk_10b19350
void UnkType_10b19350::Unk_10b19350()
{
    bool Found = false;
    for ( int i = 0; !Found && i < unk_1b25; i++ )
    {
        Found = Unk_10ee83d0(&unk_1914[i], unk_1914[i].unk_82);
    }
    if ( Found )
    {
        unk_16fc = 4;
    }
    else
    {
        unk_16fc = 0;
    }
}
