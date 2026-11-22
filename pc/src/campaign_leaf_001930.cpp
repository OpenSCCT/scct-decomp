// campaign_leaf_001930.cpp -- method at VA 0x10901930 taking two arguments: calls virtual slot 4
// (vtable offset 0x10) with its first argument and returns whether the result is not negative; the
// second argument is unused. The class and method names are invented; the slot is the binary's.

class UnkType_10901930
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual int VirtualSlot4(int Value);

    int Unk_10901930(int Value, int Arg1);
};

// UnkType_10901930::Unk_10901930
int UnkType_10901930::Unk_10901930(int Value, int Arg1)
{
    return VirtualSlot4(Value) >= 0;
}
