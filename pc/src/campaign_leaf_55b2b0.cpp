// campaign_leaf_55b2b0.cpp -- thiscall method at VA 0x10e5b2b0: takes a value from the fifth
// virtual method of the object at 0x20 and calls its seventh, then passes its two arguments with
// that value to the cdecl function at VA 0x110133a0 before and after calling the function at VA
// 0x11013350 (with the members at 0x24 and 0x28) and the tenth virtual method of the object, and
// ends with the function at VA 0x11013380. All names are invented.

void Unk_110133a0(int First, int Second, int Value, int Size);
void Unk_11013350(int First, int Second, int Third);
void Unk_11013380(int Value);

class UnkType_10e5b2b0_Device
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual int VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void VirtualSlot9(int First, int Second);
};

class UnkType_10e5b2b0
{
public:
    void Unk_10e5b2b0(int First, int Second);

private:
    int unk_00[8];
    UnkType_10e5b2b0_Device* unk_20;
    int unk_24;
    int unk_28;
};

// UnkType_10e5b2b0::Unk_10e5b2b0
void UnkType_10e5b2b0::Unk_10e5b2b0(int First, int Second)
{
    int Value = unk_20->VirtualSlot5();
    unk_20->VirtualSlot6();
    Unk_110133a0(First, Second, Value, 8);
    Unk_11013350(unk_24, unk_28, Second);
    unk_20->VirtualSlot9(First, Second);
    Unk_110133a0(First, Second, Value, 8);
    Unk_11013380(Second);
}
