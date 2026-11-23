// campaign_leaf_08c780.cpp -- method at VA 0x1098c780: passes its argument to the method at VA
// 0x1098c560 of the members at 0x38 and 0x50. The class, member and method names are invented; the
// offsets and the address are the binary's.

class UnkType_1098c560_08c780
{
public:
    void Unk_1098c560(const int& Value);
};

class UnkType_1098c780
{
public:
    void Unk_1098c780(int Value);

private:
    unsigned char unk_00[0x38];
    UnkType_1098c560_08c780 unk_38;
    unsigned char unk_39[0x50 - 0x39];
    UnkType_1098c560_08c780 unk_50;
};

// UnkType_1098c780::Unk_1098c780
void UnkType_1098c780::Unk_1098c780(int Value)
{
    unk_38.Unk_1098c560(Value);
    unk_50.Unk_1098c560(Value);
}
