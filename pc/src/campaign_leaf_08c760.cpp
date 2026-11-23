// campaign_leaf_08c760.cpp -- method at VA 0x1098c760: unless bit 2 (0x4) of the value at 0x28 of
// the object its argument points to is set, passes the pointer, by reference, to the method at VA
// 0x1093aa40 of the member at 0x38. The class, member and method names are invented; the offsets,
// the bit and the address are the binary's.

class UnkType_1098c760_Item
{
public:
    unsigned char unk_00[0x28];
    int unk_28;
};

class UnkType_1098c760_1093aa40
{
public:
    void Unk_1093aa40(UnkType_1098c760_Item* const& Item);
};

class UnkType_1098c760
{
public:
    void Unk_1098c760(UnkType_1098c760_Item* Item);

private:
    unsigned char unk_00[0x38];
    UnkType_1098c760_1093aa40 unk_38;
};

// UnkType_1098c760::Unk_1098c760
void UnkType_1098c760::Unk_1098c760(UnkType_1098c760_Item* Item)
{
    if ( !( Item->unk_28 & 4 ) )
    {
        unk_38.Unk_1093aa40(Item);
    }
}
