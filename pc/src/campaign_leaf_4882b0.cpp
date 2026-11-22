// campaign_leaf_4882b0.cpp -- constructor at VA 0x10d882b0 of a polymorphic class whose vtable is at
// VA 0x1113cb70; runs the base constructor at VA 0x10dbd740 and stores its unsigned char argument at
// offset 8. All names are invented.

class UnkType_10dbd740
{
public:
    UnkType_10dbd740();
    virtual void VirtualSlot0();

private:
    int unk_04;
};

class UnkType_10d882b0 : public UnkType_10dbd740
{
public:
    UnkType_10d882b0(unsigned char Value);
    virtual void VirtualSlot0();

private:
    unsigned char unk_08;
};

// UnkType_10d882b0::UnkType_10d882b0
UnkType_10d882b0::UnkType_10d882b0(unsigned char Value) : unk_08(Value)
{
}
