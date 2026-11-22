// campaign_leaf_464950.cpp -- constructor at VA 0x10d64950 of a polymorphic class whose vtable is at
// VA 0x1113b810; passes its argument to the base constructor at VA 0x10d63c30. All names are
// invented.

class UnkType_10d63c30
{
public:
    UnkType_10d63c30(int Value);
    virtual void VirtualSlot0();
};

class UnkType_10d64950 : public UnkType_10d63c30
{
public:
    UnkType_10d64950(int Value);
    virtual void VirtualSlot0();
};

// UnkType_10d64950::UnkType_10d64950
UnkType_10d64950::UnkType_10d64950(int Value) : UnkType_10d63c30(Value)
{
}
