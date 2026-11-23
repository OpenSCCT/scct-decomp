// campaign_leaf_2b34b0.cpp -- a member function at VA 0x10bb34b0 that clears a local 100-byte
// record with the free function at VA 0x10ccad40, appends it to the array at 0x4f0 with the array's
// member at VA 0x10bb1eb0, and then stores its argument at 0x00 and -1 at 0x30 of the array's last
// element. The class, method and member names are invented; the offsets, sizes and addresses are
// the binary's.

void Unk_10ccad40(void* Dest, int Value, int Count);

struct UnkType_10bb34b0_Item
{
    int unk_00;
    unsigned char unk_04[0x30 - 0x04];
    int unk_30;
    unsigned char unk_34[0x64 - 0x34];
};

class UnkType_10bb34b0_Array
{
public:
    void Unk_10bb1eb0(const UnkType_10bb34b0_Item& Item);

    // guess: the array's last element (an inline accessor; the name is invented)
    UnkType_10bb34b0_Item& Last()
    {
        return unk_00[unk_04 - 1];
    }

    UnkType_10bb34b0_Item* unk_00;
    int unk_04;
};

class UnkType_10bb34b0
{
public:
    void Unk_10bb34b0(int Value);

private:
    unsigned char unk_000[0x4f0];
    UnkType_10bb34b0_Array unk_4f0;
};

// UnkType_10bb34b0::Unk_10bb34b0
void UnkType_10bb34b0::Unk_10bb34b0(int Value)
{
    UnkType_10bb34b0_Item Item;
    Unk_10ccad40(&Item, 0, sizeof(Item));
    unk_4f0.Unk_10bb1eb0(Item);
    unk_4f0.Last().unk_00 = Value;
    unk_4f0.Last().unk_30 = -1;
}
