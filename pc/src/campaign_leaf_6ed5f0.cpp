// campaign_leaf_6ed5f0.cpp -- thiscall method at VA 0x10fed5f0: passes its argument to the second virtual
// method of the object at 0x08 and returns the argument. The class and method names are invented.

class UnkType_10fed5f0_08
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1(int Value);
};

class UnkType_10fed5f0
{
public:
    int Unk_10fed5f0(int Value);

private:
    int unk_00;
    int unk_04;
    UnkType_10fed5f0_08* unk_08;
};

// UnkType_10fed5f0::Unk_10fed5f0
int UnkType_10fed5f0::Unk_10fed5f0(int Value)
{
    unk_08->VirtualSlot1(Value);
    return Value;
}
