// campaign_leaf_498fa0.cpp -- constructor at VA 0x10d98fa0 of a polymorphic class whose vtable is at
// VA 0x1113df84; passes its argument and 0 to the base constructor at VA 0x10d98b40. All names
// are invented.

class UnkType_10d98b40
{
public:
    UnkType_10d98b40(int Value, int Flags);
    virtual void VirtualSlot0();
};

class UnkType_10d98fa0 : public UnkType_10d98b40
{
public:
    UnkType_10d98fa0(int Value);
    virtual void VirtualSlot0();
};

// UnkType_10d98fa0::UnkType_10d98fa0
UnkType_10d98fa0::UnkType_10d98fa0(int Value) : UnkType_10d98b40(Value, 0)
{
}
