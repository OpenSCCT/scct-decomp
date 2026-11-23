// campaign_leaf_4ae3a0.cpp -- one function at file offset 0x4ae3a0, preferred VA 0x10dae3a0.
// The constructor runs the base constructor at 0x10da4770 with Value and installs the vtable at
// 0x1113f680. The class and parameter names are invented; the offset and the bytes are the
// binary's.

class UnkType_10dae3a0_Base
{
public:
    UnkType_10dae3a0_Base(int Value);

    virtual void VirtualSlot0();
};

class UnkType_10dae3a0 : public UnkType_10dae3a0_Base
{
public:
    UnkType_10dae3a0(int Value);

    virtual void VirtualSlot0();
};

// UnkType_10dae3a0::UnkType_10dae3a0
UnkType_10dae3a0::UnkType_10dae3a0(int Value)
    : UnkType_10dae3a0_Base(Value)
{
}
