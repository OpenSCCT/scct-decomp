// campaign_leaf_08c7e0.cpp -- method at VA 0x1098c7e0: unless bit 2 (0x4) of the value at 0x28 of
// the object its argument points to is set, passes the pointer, by reference, to the method at VA
// 0x1098c4f0 of the member at 0x50. The class, member and method names are invented; the offsets,
// the bit and the address are the binary's.

class UnkType_1098c7e0_Item
{
public:
    unsigned char unk_00[0x28];
    int unk_28;
};

class UnkType_1098c7e0_1098c4f0
{
public:
    void Unk_1098c4f0(UnkType_1098c7e0_Item* const& Item);
};

class UnkType_1098c7e0
{
public:
    void Unk_1098c7e0(UnkType_1098c7e0_Item* Item);

private:
    unsigned char unk_00[0x50];
    UnkType_1098c7e0_1098c4f0 unk_50;
};

// UnkType_1098c7e0::Unk_1098c7e0
void UnkType_1098c7e0::Unk_1098c7e0(UnkType_1098c7e0_Item* Item)
{
    if ( !( Item->unk_28 & 4 ) )
    {
        unk_50.Unk_1098c4f0(Item);
    }
}
