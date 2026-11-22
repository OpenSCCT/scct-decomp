// campaign_leaf_48d040.cpp -- thiscall at VA 0x10d8d040: passes its pointer argument by reference
// to the method at VA 0x10d8cdc0 of the member at offset 0x6c, then calls the third virtual method
// of the object it points to. All names are invented.

class UnkType_10d8d040_Obj
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
};

class UnkType_10d8cdc0
{
public:
    void Unk_10d8cdc0(UnkType_10d8d040_Obj* const& Object);
};

class UnkType_10d8d040
{
public:
    void Unk_10d8d040(UnkType_10d8d040_Obj* Object);

private:
    unsigned char unk_00[0x6c];
    UnkType_10d8cdc0 unk_6c;
};

// UnkType_10d8d040::Unk_10d8d040
void UnkType_10d8d040::Unk_10d8d040(UnkType_10d8d040_Obj* Object)
{
    unk_6c.Unk_10d8cdc0(Object);
    Object->VirtualSlot2();
}
