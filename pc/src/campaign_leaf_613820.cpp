// campaign_leaf_613820.cpp -- thiscall method at VA 0x10f13820: calls the method at VA 0x10f12ca0
// with the addresses of three locals; when that returns true, passes them to virtual slot 10
// (vtable offset 0x28) of the object at 0x10 and returns true, otherwise returns false. The class,
// method and member names are invented; the offsets and addresses are the binary's.

struct UnkType_10f13820_Third
{
    unsigned char unk_00[0x10];
};

class UnkType_10f13820_Target
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
    virtual void VirtualSlot8();
    virtual void VirtualSlot9();
    virtual void VirtualSlot10(int First, int Second, UnkType_10f13820_Third* Third);
};

class UnkType_10f13820
{
public:
    bool Unk_10f13820();
    bool Unk_10f12ca0(int* First, int* Second, UnkType_10f13820_Third* Third);

private:
    unsigned char unk_00[0x10];
    UnkType_10f13820_Target* unk_10;
};

// UnkType_10f13820::Unk_10f13820
bool UnkType_10f13820::Unk_10f13820()
{
    int First;
    int Second;
    UnkType_10f13820_Third Third;

    if ( Unk_10f12ca0(&First, &Second, &Third) )
    {
        unk_10->VirtualSlot10(First, Second, &Third);
        return true;
    }
    return false;
}
