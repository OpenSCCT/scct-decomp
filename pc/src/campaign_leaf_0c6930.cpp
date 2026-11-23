// campaign_leaf_0c6930.cpp -- method at VA 0x109c6930 taking a key and flags: when flag 0x2000 is
// set, looks the key up through the method at VA 0x10990be0 of the member at 0x340 and returns 0
// when that succeeds; otherwise returns the method at VA 0x109906e0 called with the key and the
// flags with 0x10000 added. The class, member and method names are invented; the offsets, the flag
// values and the addresses are the binary's.

class UnkType_109c6930_Map
{
public:
    int Unk_10990be0(int& Key, int& Value);
};

class UnkType_109c6930
{
public:
    int Unk_109c6930(int Key, int Flags);
    int Unk_109906e0(int Key, int Flags);

private:
    unsigned char unk_00[0x340];
    UnkType_109c6930_Map unk_340;
};

// UnkType_109c6930::Unk_109c6930
int UnkType_109c6930::Unk_109c6930(int Key, int Flags)
{
    if ( Flags & 0x2000 )
    {
        int Value = 0;
        int Found = Key;
        if ( unk_340.Unk_10990be0(Found, Value) )
        {
            return 0;
        }
    }
    return Unk_109906e0(Key, Flags | 0x10000);
}
