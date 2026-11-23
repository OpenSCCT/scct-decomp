// campaign_leaf_4dbdc0.cpp -- one function at file offset 0x4dbdc0, preferred VA 0x10ddbdc0.
// The constructor runs the base constructor at 0x10dc1560 with Value, installs the vtable at
// 0x11146794, calls the method at 0x10dc14d0 with 0 and stores Extra at offset 0x1c. The class,
// method, member and parameter names are invented; the offset and the bytes are the binary's.

class UnkType_10ddbdc0_Base
{
public:
    unsigned char unk_4[0x18];

    UnkType_10ddbdc0_Base(int Value);

    virtual void VirtualSlot0();

    void Unk_10dc14d0(int State);
};

class UnkType_10ddbdc0 : public UnkType_10ddbdc0_Base
{
public:
    int unk_1c;

    UnkType_10ddbdc0(int Value, int Extra);

    virtual void VirtualSlot0();
};

// UnkType_10ddbdc0::UnkType_10ddbdc0
UnkType_10ddbdc0::UnkType_10ddbdc0(int Value, int Extra)
    : UnkType_10ddbdc0_Base(Value)
{
    Unk_10dc14d0(0);
    unk_1c = Extra;
}
