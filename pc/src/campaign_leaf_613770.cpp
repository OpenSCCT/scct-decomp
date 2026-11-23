// campaign_leaf_613770.cpp -- thiscall method at VA 0x10f13770: calls the method at VA 0x10f12810
// with the addresses of three locals; when that returns true, passes them to virtual slot 8 (vtable
// offset 0x20) of the object at 0x10 and returns true, otherwise returns false. The class, method
// and member names are invented; the offsets and addresses are the binary's.

struct UnkType_10f13770_Third
{
    unsigned char unk_00[0x10];
};

class UnkType_10f13770_Target
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8(int First, int Second, UnkType_10f13770_Third* Third);
};

class UnkType_10f13770
{
public:
    bool Unk_10f13770();
    bool Unk_10f12810(int* First, int* Second, UnkType_10f13770_Third* Third);

private:
    unsigned char unk_00[0x10];
    UnkType_10f13770_Target* unk_10;
};

// UnkType_10f13770::Unk_10f13770
bool UnkType_10f13770::Unk_10f13770()
{
    int First;
    int Second;
    UnkType_10f13770_Third Third;

    if ( Unk_10f12810(&First, &Second, &Third) )
    {
        unk_10->VirtualSlot8(First, Second, &Third);
        return true;
    }
    return false;
}
