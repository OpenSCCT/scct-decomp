// campaign_leaf_488650.cpp -- constructor at VA 0x10d88650 of a polymorphic class whose vtable is at
// VA 0x1113cbc4; runs the base constructor at VA 0x10dbd740 and stores its int argument at
// offset 8. All names are invented.

class UnkType_10dbd740
{
public:
    UnkType_10dbd740();
    virtual void VirtualSlot0();

private:
    int unk_04;
};

class UnkType_10d88650 : public UnkType_10dbd740
{
public:
    UnkType_10d88650(int Value);
    virtual void VirtualSlot0();

private:
    int unk_08;
};

// UnkType_10d88650::UnkType_10d88650
UnkType_10d88650::UnkType_10d88650(int Value) : unk_08(Value)
{
}
