// campaign_leaf_6ede30.cpp -- thiscall method at VA 0x10fede30: passes its argument to the second
// virtual method of the object at 0x08 and returns the argument. The class and method names are
// invented.

class UnkType_10fede30_08
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1(int Value);
};

class UnkType_10fede30
{
public:
    int Unk_10fede30(int Value);

private:
    int unk_00;
    int unk_04;
    UnkType_10fede30_08* unk_08;
};

// UnkType_10fede30::Unk_10fede30
int UnkType_10fede30::Unk_10fede30(int Value)
{
    unk_08->VirtualSlot1(Value);
    return Value;
}
