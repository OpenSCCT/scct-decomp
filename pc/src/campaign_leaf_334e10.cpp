// campaign_leaf_334e10.cpp -- one function at file offset 0x334e10, preferred VA 0x10c34e10. It
// adds one 0x30-byte element to this array (method at 0x10c28be0), assigns Item to it member by
// member (four 0xc-byte members assigned by the method at 0x109097e0) and returns its index. The
// class, method, member and parameter names are invented; the offsets and the bytes are the
// binary's.

class UnkType_10c34e10_Text
{
public:
    UnkType_10c34e10_Text& operator=(const UnkType_10c34e10_Text& Other);

    unsigned char unk_0[0xc];
};

struct UnkType_10c34e10_Entry
{
    UnkType_10c34e10_Text unk_0;
    UnkType_10c34e10_Text unk_c;
    UnkType_10c34e10_Text unk_18;
    UnkType_10c34e10_Text unk_24;
};

class UnkType_10c34e10
{
public:
    int Unk_10c28be0(int Size, int Count);
    int Unk_10c34e10(const UnkType_10c34e10_Entry& Item);

    UnkType_10c34e10_Entry* unk_0;
    int unk_4;
    int unk_8;
};

// UnkType_10c34e10::Unk_10c34e10
int UnkType_10c34e10::Unk_10c34e10(const UnkType_10c34e10_Entry& Item)
{
    int Index = Unk_10c28be0(0x30, 1);

    unk_0[Index] = Item;
    return Index;
}
