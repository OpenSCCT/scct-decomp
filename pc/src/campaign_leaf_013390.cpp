// campaign_leaf_013390.cpp -- method at VA 0x10913390: deletes each object in the pointer array at
// 0x2d4 (count at 0x2d8) that exists through its virtual destructor (slot 1), then calls the method
// at VA 0x1090ec40. The class, member and method names are invented; the offsets, the slot and the
// address are the binary's.

class UnkType_10913390_Item
{
public:
    virtual void VirtualSlot0();
    virtual ~UnkType_10913390_Item();
};

class UnkType_10913390
{
public:
    void Unk_10913390();
    void Unk_1090ec40();

private:
    unsigned char unk_000[0x2d4];
    UnkType_10913390_Item** unk_2d4;
    int unk_2d8;
};

// UnkType_10913390::Unk_10913390
void UnkType_10913390::Unk_10913390()
{
    for ( int i = 0; i < unk_2d8; i++ )
    {
        delete unk_2d4[i];
    }
    Unk_1090ec40();
}
