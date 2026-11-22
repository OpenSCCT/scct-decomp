// campaign_leaf_3eab10.cpp -- a member function at VA 0x10ceab10 that passes its argument to the
// member at VA 0x10cea000 and then calls virtual slot 6 of the argument's object with the address
// of the member at 0x54. guess: serializes the object through an archive after its base class. The
// class, method and member names are invented; the offsets, addresses and slot are the binary's.

class UnkType_10ceab10_Archive
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6(int* Value);
};

class UnkType_10ceab10
{
public:
    void Unk_10cea000(UnkType_10ceab10_Archive& Ar);
    void Unk_10ceab10(UnkType_10ceab10_Archive& Ar);

private:
    unsigned char unk_00[0x54];
    int unk_54;
};

// UnkType_10ceab10::Unk_10ceab10
void UnkType_10ceab10::Unk_10ceab10(UnkType_10ceab10_Archive& Ar)
{
    Unk_10cea000(Ar);
    Ar.VirtualSlot6(&unk_54);
}
