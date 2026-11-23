// campaign_leaf_08c7b0.cpp -- method at VA 0x1098c7b0: unless bit 2 (0x4) of the value at 0x28 of
// the object its argument points to is set, passes the pointer, by reference, to the method at VA
// 0x1093aa40 of the member at 0x44. The class, member and method names are invented; the offsets,
// the bit and the address are the binary's.

class UnkType_1098c7b0_Item
{
public:
    unsigned char unk_00[0x28];
    int unk_28;
};

class UnkType_1098c7b0_1093aa40
{
public:
    void Unk_1093aa40(UnkType_1098c7b0_Item* const& Item);
};

class UnkType_1098c7b0
{
public:
    void Unk_1098c7b0(UnkType_1098c7b0_Item* Item);

private:
    unsigned char unk_00[0x44];
    UnkType_1098c7b0_1093aa40 unk_44;
};

// UnkType_1098c7b0::Unk_1098c7b0
void UnkType_1098c7b0::Unk_1098c7b0(UnkType_1098c7b0_Item* Item)
{
    if ( !( Item->unk_28 & 4 ) )
    {
        unk_44.Unk_1093aa40(Item);
    }
}
