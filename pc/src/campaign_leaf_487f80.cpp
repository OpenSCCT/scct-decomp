// campaign_leaf_487f80.cpp -- constructor at VA 0x10d87f80 of a polymorphic class whose vtable is at
// VA 0x1113cb38; runs the base constructor at VA 0x10dbd740 and stores its int argument at
// offset 8. All names are invented.

class UnkType_10dbd740
{
public:
    UnkType_10dbd740();
    virtual void VirtualSlot0();

private:
    int unk_04;
};

class UnkType_10d87f80 : public UnkType_10dbd740
{
public:
    UnkType_10d87f80(int Value);
    virtual void VirtualSlot0();

private:
    int unk_08;
};

// UnkType_10d87f80::UnkType_10d87f80
UnkType_10d87f80::UnkType_10d87f80(int Value) : unk_08(Value)
{
}
