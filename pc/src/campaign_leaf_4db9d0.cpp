// campaign_leaf_4db9d0.cpp -- one function at file offset 0x4db9d0, preferred VA 0x10ddb9d0.
// The constructor runs the base constructor at 0x10ddac10 with Value, installs the vtable at
// 0x1114677c and sets the byte at offset 0x28. The class, member and parameter names are invented;
// the offset and the bytes are the binary's.

class UnkType_10ddb9d0_Base
{
public:
    unsigned char unk_4[0x24];

    UnkType_10ddb9d0_Base(int Value);

    virtual void VirtualSlot0();
};

class UnkType_10ddb9d0 : public UnkType_10ddb9d0_Base
{
public:
    bool unk_28;

    UnkType_10ddb9d0(int Value);

    virtual void VirtualSlot0();
};

// UnkType_10ddb9d0::UnkType_10ddb9d0
UnkType_10ddb9d0::UnkType_10ddb9d0(int Value)
    : UnkType_10ddb9d0_Base(Value)
{
    unk_28 = true;
}
