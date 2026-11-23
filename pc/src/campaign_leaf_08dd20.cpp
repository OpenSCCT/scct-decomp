// campaign_leaf_08dd20.cpp -- method at VA 0x1098dd20: if the pointer at 0x33c is set, calls
// virtual slot 9 (vtable offset 0x24) on the object it points to; then clears the pointer. The
// class, member and method names are invented; the offset and the slot are the binary's.

class UnkType_1098dd20_33c
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
};

class UnkType_1098dd20
{
public:
    void Unk_1098dd20();

private:
    unsigned char unk_000[0x33c];
    UnkType_1098dd20_33c* unk_33c;
};

// UnkType_1098dd20::Unk_1098dd20
void UnkType_1098dd20::Unk_1098dd20()
{
    if ( unk_33c )
    {
        unk_33c->VirtualSlot9();
    }
    unk_33c = 0;
}
