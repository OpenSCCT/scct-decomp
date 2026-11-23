// campaign_leaf_334e70.cpp -- one function at file offset 0x334e70, preferred VA 0x10c34e70. It
// adds one 0x2c-byte element to this array (method at 0x10c28c60), assigns Item to it member by
// member (a byte, a word and three 0xc-byte members assigned by the method at 0x109097e0) and
// returns its index. The class, method, member and parameter names are invented; the offsets and
// the bytes are the binary's.

class UnkType_10c34e70_Text
{
public:
    UnkType_10c34e70_Text& operator=(const UnkType_10c34e70_Text& Other);

    unsigned char unk_0[0xc];
};

struct UnkType_10c34e70_Entry
{
    unsigned char unk_0;
    int unk_4;
    UnkType_10c34e70_Text unk_8;
    UnkType_10c34e70_Text unk_14;
    UnkType_10c34e70_Text unk_20;
};

class UnkType_10c34e70
{
public:
    int Unk_10c28c60(int Size, int Count);
    int Unk_10c34e70(const UnkType_10c34e70_Entry& Item);

    UnkType_10c34e70_Entry* unk_0;
    int unk_4;
    int unk_8;
};

// UnkType_10c34e70::Unk_10c34e70
int UnkType_10c34e70::Unk_10c34e70(const UnkType_10c34e70_Entry& Item)
{
    int Index = Unk_10c28c60(0x2c, 1);

    unk_0[Index] = Item;
    return Index;
}
