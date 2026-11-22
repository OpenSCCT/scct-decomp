// campaign_leaf_54f450.cpp -- one function at file offset 0x54f450, preferred VA 0x10e4f450. It
// appends Count items to Out: first the free items popped from the pointer stack at 0x8 (count
// at 0xc), then fresh 0x50-byte items taken in order from the pool at 0x1b0 (next index at
// 0x1b4). The class, method, structure, member and parameter names are invented; the offsets and
// the bytes are the binary's.

struct UnkType_10e4f450_Item
{
    unsigned char unk_0[0x50];
};

struct UnkType_10e4f450_List
{
    UnkType_10e4f450_Item** unk_0;
    int unk_4;
};

class UnkType_10e4f450
{
public:
    void Unk_10e4f450(UnkType_10e4f450_List& Out, int Count);

    unsigned char unk_0[0x8];
    UnkType_10e4f450_Item** unk_8;
    int unk_c;
    unsigned char unk_10[0x1a0];
    UnkType_10e4f450_Item* unk_1b0;
    int unk_1b4;
};

// UnkType_10e4f450::Unk_10e4f450
void UnkType_10e4f450::Unk_10e4f450(UnkType_10e4f450_List& Out, int Count)
{
    int Index = unk_c - 1;

    for ( ; Count != 0 && Index >= 0; Count--, Index-- )
    {
        Out.unk_0[Out.unk_4] = unk_8[Index];
        Out.unk_4++;
        unk_c--;
    }
    for ( ; Count > 0; Count-- )
    {
        int Next = unk_1b4++;

        Out.unk_0[Out.unk_4] = &unk_1b0[Next];
        Out.unk_4++;
    }
}
