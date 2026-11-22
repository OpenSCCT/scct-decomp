// campaign_leaf_466890.cpp -- thiscall at VA 0x10d66890: calls the third virtual method of the
// object at offset 0x20, then clears the byte at offset 0x24. All names are invented.

class UnkType_10d66890_Obj
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
};

class UnkType_10d66890
{
public:
    void Unk_10d66890();

private:
    unsigned char unk_00[0x20];
    UnkType_10d66890_Obj* unk_20;
    unsigned char unk_24;
};

// UnkType_10d66890::Unk_10d66890
void UnkType_10d66890::Unk_10d66890()
{
    unk_20->VirtualSlot2();
    unk_24 = 0;
}
